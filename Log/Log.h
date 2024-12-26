#ifndef __LOG_H__
#define __LOG_H__

#pragma warning( disable : 4996 )
#include <vector>
#include <string>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOGINFO(__MESSAGE__, ...)	Log::Set(Log::Type::eInfo, __FILENAME__, __LINE__, __MESSAGE__, __VA_ARGS__);
#define LOGERROR(__MESSAGE__, ...)	Log::Set(Log::Type::eError, __FILENAME__, __LINE__, __MESSAGE__, __VA_ARGS__);
#define LOGWARN(__MESSAGE__, ...)	Log::Set(Log::Type::eWarn, __FILENAME__, __LINE__, __MESSAGE__, __VA_ARGS__);

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

	void Set(const Type _eType, const char* _pFileName, const unsigned int _nLine, const char* _pMessage, ...);
	const std::vector<std::string> Get(const Type _eType = Type::eVerbose);

	namespace Handler
	{
		void Init(const unsigned short _nMaxCount);
		void Print(const Type _eType = Type::eVerbose);
		void Clear();
	};
};

#endif // __LOG_H__