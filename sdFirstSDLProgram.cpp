/* Based on Lazy Foo's Beginning Game Programming v2.0 */
/* http://lazyfoo.net/tutorials/SDL/index.php */
/* Getting started: http://lazyfoo.net/SDL_tutorials/lesson01/windows/msvsnet2010e/index.php */

//INPUT, the program will render the numbers using images, and read the numbers aloud using pre recorded wavs

#define PHONENUMBER "7783217954"

//end INPUT

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include <sstream>
#include <iostream>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *one = NULL;
Mix_Chunk *two = NULL;
Mix_Chunk *three = NULL;
Mix_Chunk *four = NULL;
Mix_Chunk *five = NULL;
Mix_Chunk *six= NULL;
Mix_Chunk *seven = NULL;
Mix_Chunk *eight = NULL;
Mix_Chunk *nine = NULL;
Mix_Chunk *zero = NULL;
Mix_Chunk *audioMsg= NULL;
SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Monitor Music", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );

    //Open the font
    font = TTF_OpenFont( "ghoul.ttf", 22 );

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //Load the music
    music = Mix_LoadMUS( "beat.wav" );

    //If there was a problem loading the music
    if( music == NULL )
    {
        return false;
    }

one = Mix_LoadWAV( "one.wav");
two = Mix_LoadWAV( "two.wav");
three = Mix_LoadWAV( "three.wav");
four = Mix_LoadWAV( "four.wav");
five = Mix_LoadWAV( "five.wav");
six= Mix_LoadWAV( "six.wav");
seven = Mix_LoadWAV( "seven.wav");
eight = Mix_LoadWAV( "eight.wav");
nine = Mix_LoadWAV( "nine.wav");
zero = Mix_LoadWAV( "zero.wav");
audioMsg = Mix_LoadWAV( "audioMsg.wav");





    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );

    //Free the music
    Mix_FreeMusic( music );

    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}




//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }
	//init
    apply_surface( 0, 0, background, screen );

    //Render the text
    message = TTF_RenderText_Solid( font, "Your phone number is", textColor );

    //Show the message on the screen
    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 100, message, screen );
		SDL_Flip( screen );
		Mix_PlayChannel( -1, audioMsg, 0 ); // 
	SDL_Delay(3333);


	std::stringstream phoneNumberStream;
	std::stringstream phoneNumberStreamDisplay;
	std::string phoneNumberString;
	std::string phoneNumberStringDisplay;
	

	std::cin >> phoneNumberString;   // user enters his phone number


	//phoneNumberStream << phoneNumberString; // put this into a container
	phoneNumberStream << PHONENUMBER;

	char ch;

	while ( phoneNumberStream.good() )
	{
		ch = phoneNumberStream.get();
		    //Apply the background
    apply_surface( 0, 0, background, screen );

    //Render the text
    message = TTF_RenderText_Solid( font, "The phone number you have entered is", textColor );

    //Show the message on the screen
    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 100, message, screen );

		phoneNumberStreamDisplay << ch; 


		phoneNumberStringDisplay = phoneNumberStreamDisplay.str();

    //Render the text
		message = TTF_RenderText_Solid( font, phoneNumberStringDisplay.c_str(), textColor );

    //Show the message on the screen
    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 200, message, screen );
    //Update the screen
	SDL_Flip( screen );


	switch (ch)
	{
	case '1':	Mix_PlayChannel( -1, one, 0 ); break;
	case '2':	Mix_PlayChannel( -1, two, 0 ); break;
	case '3':	Mix_PlayChannel( -1, three, 0 ); break;
	case '4':	Mix_PlayChannel( -1, four, 0 ); break;
	case '5':	Mix_PlayChannel( -1, five, 0 ); break;
	case '6':	Mix_PlayChannel( -1, six, 0 ); break;
	case '7':	Mix_PlayChannel( -1, seven, 0 ); break;
	case '8':	Mix_PlayChannel( -1, eight, 0 ); break;
	case '9':	Mix_PlayChannel( -1, nine, 0 ); break;
	case '0':	Mix_PlayChannel( -1, zero, 0 ); break;
	}



	SDL_Delay(1000);
	}







    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
    }

    //Free surfaces, fonts and sounds
    //then quit SDL_mixer, SDL_ttf and SDL
    clean_up();

    return 0;
}
