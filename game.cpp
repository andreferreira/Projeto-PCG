#include "game.h"
#include "geometry.h"
#include "luaenv.h"
#include "timer.h"
#include "controleteclado.h"
#include "controlewii.h"
#include "shotmanager.h"

void Game::loadMap(std::string mapname) {
	if (mapa != NULL)
		delete mapa;
	mapa = new Mapa(mapname,this);
}

void Game::addPlatform(Platform* plat) {
	gravityManager->addPlatform(plat);
}

void Game::removePlatforms() {
	gravityManager->removePlatforms();
}

bool init_GL() {
    //Set clear color
    glClearColor( 1, 1, 1, 0 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Linhas
    glLineWidth(2.5);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    //If everything initialized
    return true;
}

Game::Game(ConfigManager *cfg) {
	gravityManager = new GravityManager;
	mapa = NULL;
	player = NULL;
	config = cfg;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        //erro
    }

    //Create Window
    if( SDL_SetVideoMode( config->screen["width"], config->screen["height"], config->screen["bpp"], SDL_OPENGL ) == NULL )
    {
        //erro
    }

    //Initialize OpenGL
    if( !init_GL() )
    {
        //erro
    }

    //Set caption
    SDL_WM_SetCaption( "Prototipo Jogo", NULL );
}

void Game::desenhaMira(Ponto aim) {
	glPushMatrix();
		glTranslatef(camera.x+aim.x,camera.y+aim.y,0);
		drawCircle(10,10);
	glPopMatrix();
}

void Game::show() {
	glClear( GL_COLOR_BUFFER_BIT );
    double x, y;
	int width = config->screen["width"];
	int height = config->screen["height"];
	
    if (player->getX() <= width/2)
    	x = 0;
    else if (player->getX() >= mapa->xmax() - width/2)
    	x = mapa->xmax() - width;
    else
    	x = player->getX() - width/2;

    if (player->getY() <= 2*height/3)
    	y = 0;
    else if (player->getY() >= mapa->ymax() - height/3)
    	y = mapa->ymax() - height;
    else
    	y = player->getY() - 2*height/3;
	camera.x = x;
	camera.y = y;
	player->desenha();
	mapa->desenha();
	shotManager->desenha();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( camera.x, camera.x+width, camera.y+height, camera.y, -1, 1 );
	SDL_GL_SwapBuffers();
}

void Game::reloadLua() {
	config->load();
	loadMap(config->maps.front());
	weaponManager->loadWeapons();
	player->equip(weaponManager->getWeapon("Shotgun"));
}

void Game::setSpawn(Ponto spawn) {
	this->spawn = spawn;
}

void Game::mainLoop() {
	Timer fps;
	
	loadMap(config->maps.front());

	player = new Player(this, spawn, config->player["speed"]);
	if (true) 
		ControleTeclado c(*player);
	else
		ControleWii c(*player);
	
	shotManager = new ShotManager;
	weaponManager = new WeaponManager(this);
	weaponManager->loadWeapons();
	player->equip(weaponManager->getWeapon("Shotgun"));

	bool quit = false;
	while (!quit) {
		fps.start();
		//player events
		c.handleEvents();

		//colision, gravity
		gravityManager->update();

		//movements
		player->move();
		shotManager->move();
		quit = c.getQuit();
		show();
		if (fps.get_ticks() < 1000 / config->screen["fps"] ) {
			SDL_Delay( ( 1000 / config->screen["fps"] ) - fps.get_ticks() );
		}
	}
	SDL_Quit();
}
