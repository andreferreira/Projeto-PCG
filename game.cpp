#include "game.h"
#include "geometry.h"
#include "luaenv.h"
#include "timer.h"
#include "player.h"
#include "controle.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;


const double alturachao = 400.0;


void Game::geraMapa() {
	Linha chao(0.0,alturachao,SCREEN_WIDTH,alturachao);
	mapa.push_back(chao);
	Linha plat1(30,350,100,350);
	mapa.push_back(plat1);
	Linha plat2(200,320,250,320);
	mapa.push_back(plat2);
	Linha plat3(400,275,450,275);
	mapa.push_back(plat3);
	Linha plat4(200,200,250,200);
	mapa.push_back(plat4);
	Linha plat5(30,100,100,100);
	mapa.push_back(plat5);
	for (int i = 0; i < mapa.size();i++)
		gravityManager->addPlataform(&mapa[i]);
}

bool init_GL()
{
    //Set clear color
    glClearColor( 1, 1, 1, 0 );

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

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
    if( init_GL() == false )
    {
        //erro
    }

    //Set caption
    SDL_WM_SetCaption( "Prototipo Jogo", NULL );

}

void Game::show() {
	glClear( GL_COLOR_BUFFER_BIT );
	player->desenha();
	std::vector<Linha>::iterator it;
	for (it = mapa.begin(); it != mapa.end(); it++)
		it->desenha();
	SDL_GL_SwapBuffers();
}

void Game::update(){

}


void Game::mainLoop() {
	luaRun luaEnv;
	luaEnv.registerScripts();
	luaEnv.loadScripts();
	geraMapa();
	Timer fps;

	player = new Player(this);
	Controle c(*player);
	bool quit = false;
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
}
