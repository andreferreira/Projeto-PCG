#include "game.h"
#include "geometry.h"
#include "luaenv.h"
#include "timer.h"
#include "controlewii.h"
#include "shotmanager.h"
#include "weaponitem.h"
#include "enemy.h"

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

	//Z-buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

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
    if( SDL_SetVideoMode( config->screen["width"], config->screen["height"], config->screen["bpp"], SDL_OPENGL | SDL_RESIZABLE ) == NULL )
    {
        //erro
    }

    //Initialize OpenGL
    if( !init_GL() )
    {
        //erro
    }

    //Set caption
    SDL_WM_SetCaption( "Big Stick", NULL );
}

void Game::desenhaMira(Ponto aim) {
	glPushMatrix();
		glTranslatef(aim.x,aim.y,0);
		drawCircle(10,10);
	glPopMatrix();
}

void Game::show() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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
	enemyManager->desenha();
	
	double vida = std::max(0.0,player->hp/double(MAXHP));
	
	glPushMatrix();
		glTranslatef(camera.x,camera.y,0);
		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(10,10,0);
			glVertex3f(50,10,0);
			glVertex3f(50,500,0);
			glVertex3f(10,500,0);
		glEnd();
		glColor3f(1,0,0);
		glBegin(GL_POLYGON);
			glVertex3f(10+1,10+1,0);
			glVertex3f(50-1,10+1,0);
			glVertex3f(50-1,std::max(vida*(500-1)-1,10.0),0);
			glVertex3f(10+1,std::max(vida*(500-1)-1,10.0),0);
		glEnd();
		glColor3f(0,0,0);
	glPopMatrix();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( camera.x, camera.x+width, camera.y+height, camera.y, -2, 2 );
	SDL_GL_SwapBuffers();
}

void Game::reloadLua() {
	config->load();
	resize(config->screen["width"], config->screen["height"]);
	loadMap(config->currentMap());
	weaponManager->loadWeapons();
	shotManager->clearShots();
	player->equip(weaponManager->getWeapon("Shotgun"));
}

void Game::setSpawn(Ponto spawn) {
	this->spawn = spawn;
}

void Game::resize(GLsizei x, GLsizei y) {
	config->screen["width"] = x;
	config->screen["height"] = y;
	SDL_SetVideoMode(x, y, config->screen["bpp"], SDL_OPENGL | SDL_RESIZABLE);
	glViewport(0, 0, x, y);
}

WeaponItem* Game::dropWeapon(std::string name) {
	return weaponManager->getItem(name);
}

void Game::spawnEnemy(std::string name, Ponto position) {
	Enemy* enemy = enemyManager->createEnemy(name);
	enemy->setPosition(position.x,position.y);
}

void Game::previousMap() {
	enemyManager->loadEnemies();
	shotManager->clearShots();
	loadMap(config->previousMap());
	player->setPosition(spawn.x, spawn.y);
}

void Game::reloadMap(bool respawn) {
	enemyManager->loadEnemies();
	shotManager->clearShots();
	loadMap(config->currentMap());
	if (respawn)
		player->setPosition(spawn.x, spawn.y);
}

void Game::nextMap() {
	enemyManager->loadEnemies();
	shotManager->clearShots();
	loadMap(config->nextMap());
	player->setPosition(spawn.x, spawn.y);
}

void Game::mainLoop() {
	Timer fps;
	shotManager = new ShotManager;
	weaponManager = new WeaponManager(this);
	collisionManager = new CollisionManager;
	weaponManager->loadWeapons();
	enemyManager = new EnemyManager(this);
	enemyManager->loadEnemies();
	loadMap(config->currentMap());
	
	player = new Player(this, spawn, config->player["speed"]);
	Controle *c;
	c = new ControleWii(*player);
	player->equip(weaponManager->getWeapon("Shotgun"));

	collisionManager->subscribe(player);
	std::list<WeaponItem*>::iterator itW;
	for (itW = mapa->items.begin(); itW != mapa->items.end(); itW++) {
		collisionManager->subscribe(*itW);
		gravityManager->subscribe(*itW);
	}
	
	bool quit = false;
	rate = 1.0;
	while (!quit) {
		int ifps = config->screen["fps"];
		fps.start();
		//player events
		c->handleEvents();
		enemyManager->think();
		
		//collision, gravity
		collisionManager->update();
		gravityManager->update();
		
		player->animate();
		enemyManager->animate();

		//movements
		player->move();
		shotManager->move();
		enemyManager->move();
		mapa->move();
		quit = c->getQuit();
		show();
		rate = ((double)fps.get_ticks())/ifps;
		if (rate < 1.0)
			rate = 1.0;
		if (fps.get_ticks() < 1000 / ifps ) {
			SDL_Delay( ( 1000 / ifps ) - fps.get_ticks() );
		}
	}
	SDL_Quit();
}
