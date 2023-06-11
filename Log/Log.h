#ifndef __LOG_H__
#define __LOG_H__

#include "Timer.h"
#include <vector>
#include <iostream>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#pragma warning( disable : 4996 )

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
		static void Print();

	private :
		static Log m_Log;
		static std::vector<std::string> m_Message;
};

#endif // __LOG_H__