#include "Log.h"

Log::Log() {}

Log::~Log() {}

void Log::Info( const char* Str, ... )
{
	char Buff[ MAX_LENGTH ] = "INFO ";

	va_list pArg;
	va_start( pArg, Str );
	vsprintf( Buff + strlen( Buff ), Str, pArg );
	va_end( pArg );

	std::string Temp = Timer::Get() + " | " + Buff;

	m_Message.push_back( Temp );
}

void Log::Error( const char* Str, ... )
{
	char Buff[ MAX_LENGTH ] = "ERROR ";

	va_list pArg;
	va_start( pArg, Str );
	vsprintf( Buff + strlen( Buff ), Str, pArg );
	va_end( pArg );

	std::string Temp = Timer::Get() + " | " + Buff;

	m_Message.push_back( Temp );
}

void Log::Warn( const char* Str, ... )
{
	char Buff[ MAX_LENGTH ] = "WARN ";

	va_list pArg;
	va_start( pArg, Str );
	vsprintf( Buff + strlen( Buff ), Str, pArg );
	va_end( pArg );

	std::string Temp = Timer::Get() + " | " + Buff;

	m_Message.push_back( Temp );
}

std::vector< std::string>& Log::GetMessage() { return m_Message; }
void Log::Clear() { m_Message.clear(); }

void Log::Print()
{

#ifdef _WIN32 // Windows
	AllocConsole();
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	DWORD CharsWritten;

	for ( auto Message : m_Message )
	{
		Message += "\n";
		WriteConsole( hConsole, Message.c_str(), strlen( Message.c_str() ), &CharsWritten, NULL );
	}

#elif __linux__ // Linux
	for ( auto Message : m_Message )
	{
		std::cout << Message << std::endl;
	}
#endif

	system("pause");

#ifdef __WIN32 // Windows
	FreeConsole();
#endif

}

Log Log::m_Log;
std::vector< std::string > Log::m_Message;