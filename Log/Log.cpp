#include "Log.h"
#include "VarUtils.h"

#include <stdarg.h>
#include <map>

namespace LogStorage
{
	struct LogTypeCompare
	{
		bool operator()(const Log::Type& _lhs, const Log::Type& _rhs) const
		{
			return _lhs < _rhs;
		}
	};

	std::vector<std::string> m_vLogMessage;
	std::map<Log::Type, std::vector<unsigned short>, LogTypeCompare> m_mLogType;
}

void Log::SetLog(const Type _eType, const char* _pFileName, const unsigned int _nLine, const char* _pMessage, ...)
{
	std::string strMessage = "[Time] " + VarUtils::GetTime();

	strMessage += " [Type] ";
	switch(_eType)
	{
		case Type::eInfo :
		{
			strMessage += "INFO";
			break;
		}

		case Type::eError :
		{
			strMessage += "ERROR";
			break;
		}

		case Type::eWarn :
		{
			strMessage += "WARN";
			break;
		}

		case Type::eUnknown :
		{
			strMessage += "UNKNOWN";
			break;
		}
	}

	if (nullptr != _pFileName)
	{
		strMessage += " [File] " + std::string(_pFileName);
	}

	strMessage += " [Line] " + std::to_string(_nLine);

	va_list pArgs;
	va_start(pArgs, _pMessage);
	strMessage += " [Log] " + VarUtils::GetString(_pMessage, pArgs);
	va_end(pArgs);

	const unsigned short logIndex = static_cast<unsigned short>(LogStorage::m_vLogMessage.size());
	LogStorage::m_vLogMessage.push_back(strMessage);

	if ((_eType == Type::eInfo) 
		|| (_eType == Type::eError)
		|| (_eType == Type::eWarn))
	{
		LogStorage::m_mLogType[_eType].push_back(logIndex);
	}
}

const std::vector<std::string> Log::GetLog(const Type _eType)
{
	std::vector<std::string> vLogMessage;

	const auto itr = LogStorage::m_mLogType.find(_eType);
	if (itr != LogStorage::m_mLogType.end())
	{
		const auto vLogIndex = itr->second;
		for (const auto index : vLogIndex)
		{
			const auto logMessage = LogStorage::m_vLogMessage[index];
			vLogMessage.emplace_back(logMessage);
		}
	}
	else
	{
		vLogMessage = LogStorage::m_vLogMessage;
	}

	return vLogMessage;
}

void Log::Clear()
{
	LogStorage::m_vLogMessage.clear();
	LogStorage::m_mLogType.clear();
}

void Log::Print(const Type _eType)
{
	const auto vLogMessage = GetLog(_eType);

	for (auto logMessage : vLogMessage)
	{
		printf("%s\n", logMessage.c_str());
	}
}