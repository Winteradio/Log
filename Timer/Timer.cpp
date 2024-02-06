#include "Timer.h"

std::string Timer::m_CurrentTime;
std::string Timer::m_ValueString;

#ifdef __linux__
	char m_Temp[ MAX_LENGTH ];
    struct timeval Timer::m_TimeVal;
    struct tm* Timer::m_pCurrentTimeSec;
    time_t Timer::m_CurrentTimeSec;
#endif