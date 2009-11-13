#include "game.h"
#include "geometry.h"
#include "luaenv.h"
#include "timer.h"
#include "controleteclado.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

void Game::loadMap(std::string mapname) {
	if (mapa != NULL)
		delete mapa;
	const double alturaChao = 400;
	mapa = new Mapa(mapname,this);
}

void Game::addPlatform(Platform* plat) {
	gravityManager->addPlatform(plat);
}

void Game::removePlatforms() {
	gravityManager->removePlatforms();
}

bool init_GL()
{
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

Game::Game()
{
	gravityManager = new GravityManager;
	mapa = NULL;
	player = NULL;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        //erro
    }

    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
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

    if (player->getX() <= SCREEN_WIDTH/2)
    	x = 0;
    else if (player->getX() >= mapa->xmax() - SCREEN_WIDTH/2)
    	x = mapa->xmax() - SCREEN_WIDTH;
    else
    	x = player->getX() - SCREEN_WIDTH/2;

    if (player->getY() <= 2*SCREEN_HEIGHT/3)
    	y = 0;
    else if (player->getY() >= mapa->ymax() - SCREEN_HEIGHT/3)
    	y = mapa->ymax() - SCREEN_HEIGHT;
    else
    	y = player->getY() - 2*SCREEN_HEIGHT/3;
	camera.x = x;
	camera.y = y;
	player->desenha();
	mapa->desenha();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( camera.x, camera.x+SCREEN_WIDTH, camera.y+SCREEN_HEIGHT, camera.y, -1, 1 );
	SDL_GL_SwapBuffers();
}

void Game::reloadLua() {
	loadMap(currentMap);
	weaponManager->loadWeapons();
	player->equip(weaponManager->getWeapon("Shotgun"));
}

void Game::setSpawn(Ponto spawn) {
	this->spawn = spawn;
}

void Game::mainLoop() {
	luaRun luaEnv;
	luaEnv.registerScripts();
	luaEnv.loadScripts();
	Timer fps;

	player = new Player(this);
	currentMap = "map1.lua";
	loadMap(currentMap);
	player->setPosition(spawn.x,spawn.y);
	ControleTeclado c(*player);
	bool quit = false;
	weaponManager = new WeaponManager;
	weaponManager->loadWeapons();
	player->equip(weaponManager->getWeapon("Shotgun"));
	while (!quit) {
		fps.start();
		//player events
		c.eventLoop();

		//colision, gravity
		gravityManager->update();

		//movements
		player->move();
		quit = c.getQuit();
		show();
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}
	SDL_Quit();
}
