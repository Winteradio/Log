#ifndef __LOG_H__
#define __LOG_H__

#pragma warning( disable : 4996 )

#include "LogConstants.h"
#include "LogMessage.h"

#include <string.h>

namespace Log
{
	void Init(const unsigned short _nMaxCount, const uint8_t _eMode, const uint8_t _eLevel);

	void SetCount(const unsigned short _nMaxCount);
	void SetMode(const uint8_t _eMode);
	void SetLevel(const uint8_t _eLevel);

	void Print(const uint8_t _eType);

	std::weak_ptr<Handler> GetHandler(const Enum::eType _eType);
};

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOGDATA(__TYPE__)	Log::MetaData(__TYPE__, __FILENAME__, __FUNCTION__, __LINE__), Log::GetHandler(__TYPE__)

#define LOG()			Log::Message(LOGDATA(Log::Enum::eType_None))
#define LOGINFO()		Log::Message(LOGDATA(Log::Enum::eType_Info))
#define LOGWARN()		Log::Message(LOGDATA(Log::Enum::eType_Warn))
#define LOGERROR()		Log::Message(LOGDATA(Log::Enum::eType_Error))

#define EXCEPT(__VALUE__)	std::move(__VALUE__)
		

#endif // __LOG_H__