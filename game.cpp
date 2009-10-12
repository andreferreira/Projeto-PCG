#include "game.h"
#include "geometry.h"
#include "plataformas.h"
#include "luaenv.h"
#include "timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;


const double alturachao = 400.0;

Linha chao(0.0,alturachao,SCREEN_WIDTH,alturachao);
std::vector<Linha> mapa;

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
	std::vector<Linha>::iterator it;
	for (it = mapa.begin(); it != mapa.end(); it++)
		it->desenha();
	glPushMatrix();
		glTranslatef(300,300,0);
		drawCircle(20,30);
	glPopMatrix();
	SDL_GL_SwapBuffers();
}

void Game::update(){
	
}


void Game::mainLoop() {
	luaRun luaEnv;
	luaEnv.registerScripts();
	luaEnv.loadScripts();
	mapa = geraMapa(20);
	mapa.push_back(chao);
	Timer fps;
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		fps.start();
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
                quit = true;
            }
		}
		show();
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}
}
