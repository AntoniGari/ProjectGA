#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL/include/SDL_rect.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned __int32 uint32;

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deletes a buffer
#define RELEASE( x ) \
    { \
       if( x != nullptr ) \
       { \
         delete x; \
	     x = nullptr; \
       } \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{  \
       if( x != nullptr ) \
       { \
           delete[] x; \
	       x = nullptr; \
		 } \
	 }

/* Golden Axe Arcade information
HORIZONTAL                   VERTICAL
Scan Frequency: 15.72 KHz    Scan Frequency: 60.0 Hz
Scan Period: 63.6 µSec       Scan Period: 16.7 mSec
Active Video: 46.9 µSec      Active Video: 15.3 mSec
Video Delay: 11.9 µSec       Video Delay:  1.2 mSec
Sync Pulse:  4.7 µSec        Sync Pulse:  0.2 mSec
Scan Line: 456 Pixels        Screen: 262 Lines
Resolution: 336 Pixels       Resolution: 240 Lines
Clock Freq: 7.16 MHz
*/

// Configuration -----------
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224
#define SCREEN_SIZE 3
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Golden Axe"
#define VERSION "v0.1"
#define MAX_LEVELS 1
#define ATTACK_DISTANCE 25

#endif //__GLOBALS_H__