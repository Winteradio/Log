#ifndef __LOG_H__
#define __LOG_H__

#include "Timer.h"
#include "vector"

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#pragma warning( disable : 4996 )

#ifdef _WIN32
	// Windows Code
	#pragma comment(linker, "/entry:WinMainCRTStartup")
	#pragma comment(linker, "/subsystem:console")
#endif

class Log
{
	private :
		Log();
		~Log();

	public :
		static void Info( const char* Str, ... );
		static void Error( const char* Str, ... );
		static void Warn( const char* Str, ... );

		static std::vector<std::string>& GetMessage();
		static void Clear();

	private :
		static Log m_Log;
		static std::vector<std::string> m_Message;
};

#endif // __LOG_H__