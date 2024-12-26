#ifndef __LOG_H__
#define __LOG_H__

#pragma warning( disable : 4996 )
#include <vector>
#include <string>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOGINFO(__MESSAGE__, ...)	Log::SetLog(Log::Type::eInfo, __FILENAME__, __LINE__, __MESSAGE__, __VA_ARGS__);
#define LOGERROR(__MESSAGE__, ...)	Log::SetLog(Log::Type::eError, __FILENAME__, __LINE__, __MESSAGE__, __VA_ARGS__);
#define LOGWARN(__MESSAGE__, ...)	Log::SetLog(Log::Type::eWarn, __FILENAME__, __LINE__, __MESSAGE__, __VA_ARGS__);

namespace Log
{
	enum class Type : unsigned char
	{
		eUnknown = 0,
		eInfo,
		eError,
		eWarn,
		eVerbose
	};

	void SetLog(const Type _eType, const char* _pFileName, const unsigned int _nLine, const char* _pMessage, ...);

	const std::vector<std::string> GetLog(const Type _eType = Type::eVerbose);

	void Clear();
	void Print(const Type _eType = Type::eVerbose);
};

#endif // __LOG_H__