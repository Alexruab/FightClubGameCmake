#include "DoodleJump.h"
/*
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif


#if defined(_WIN32) 
    #include <Windows.h> // or any library that uses Windows.h
#endif

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif
*/
#include <iostream>

int main(void)
{

    DoodleJump game;
    game.run(); 

    return EXIT_SUCCESS;
}