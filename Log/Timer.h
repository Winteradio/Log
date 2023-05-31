#ifndef __TIMER_H__
#define __TIMER_H__

#define MAX_LENGTH 512

#include <string>

#ifdef _WIN32
	#include <windows.h>
#elif __linux__
	#include <sys/time.h>
#endif

class Timer
{
	public :
		static std::string Get()
		{
			m_CurrentTime.clear();

#ifdef _WIN32 
			// Windows Code
			SYSTEMTIME sysTime;
			GetLocalTime( &sysTime );

			m_CurrentTime += CheckNumOfDigits( sysTime.wHour, 2 ) + ":";
			m_CurrentTime += CheckNumOfDigits( sysTime.wMinute, 2 ) + ":";
			m_CurrentTime += CheckNumOfDigits( sysTime.wSecond, 2 ) + ":";
			m_CurrentTime += CheckNumOfDigits( sysTime.wMilliseconds, 3 );
#elif __linux__
			// Linux code
			gettimeofday( &m_TimeVal, nullptr);

			m_CurrentTimeSec = m_TimeVal.tv_sec;
			m_pCurrentTimeSec = localtime( &m_CurrentTimeSec );

			strftime( m_Temp, sizeof( m_Temp ), "%H:%M:%S", m_pCurrentTimeSec );

			m_CurrentTime += m_Temp;
			m_CurrentTime += ":";
			m_CurrentTime += std::to_string( m_TimeVal.tv_usec / 1000);
#endif
			return m_CurrentTime;
		}

		static std::string CheckNumOfDigits( int Value, int NumDigits )
		{
			m_ValueString.clear();
			m_ValueString = std::to_string( Value );
			while( m_ValueString.length() < NumDigits )
			{
				m_ValueString = "0" + m_ValueString;
			}
			return m_ValueString;
		}

	private :
		static char m_Temp[ MAX_LENGTH ];
		static std::string m_CurrentTime;
		static std::string m_ValueString;

#ifdef __linux__
		static struct timeval m_TimeVal;
		static struct tm* m_pCurrentTimeSec;
		static time_t m_CurrentTimeSec;
#endif

};

#endif // __TIMER_H__