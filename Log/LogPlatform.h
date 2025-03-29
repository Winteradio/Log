#ifndef __LOG_PLATFORM_H__
#define __LOG_PLATFORM_H__

#ifdef _WIN32
    #include <windows.h>
        #pragma comment(linker, "/entry:WinMainCRTStartup")
        #pragma comment(linker, "/subsystem:console")

    #define MAIN() CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
    #define PLATFORM_WINDOWS

#elif __linux__
	#include <chrono>
    #define MAIN() main()
    #define PLATFORM_LINUX
#endif


#endif // __LOG_PLATFORM_H__