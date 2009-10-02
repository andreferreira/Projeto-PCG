#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <time.h>
#include "plataforma.h"
#include "plataformas.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
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

bool init()
{
	
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        return false;
    }

    //Initialize OpenGL
    if( init_GL() == false )
    {
        return false;
    }

    //Set caption
    SDL_WM_SetCaption( "Prototipo Plataformas", NULL );

    return true;
}

const double alturachao = 400.0;

Plataforma chao(0.0,alturachao,SCREEN_WIDTH,alturachao);
std::vector<Plataforma> mapa;


void desenhaMundo() {
	glClear( GL_COLOR_BUFFER_BIT );
	std::vector<Plataforma>::iterator it;
	for (it = mapa.begin(); it != mapa.end(); it++)
		it->desenha();
	SDL_GL_SwapBuffers();
}

int main() {
	init();
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
		desenhaMundo();
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}
}
