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

	unsigned short m_nMaxCount = 1024;
	std::vector<std::string> m_vLogMessage;
	std::map<Log::Type, std::vector<unsigned short>, LogTypeCompare> m_mLogType;
}

namespace Log
{
	std::string ConvertTypeToString(const Type _eType)
	{
		std::string strType;

		if (_eType == Type::eInfo)
		{
			strType += "INFO";
		}
		else if (_eType == Type::eError)
		{
			strType += "ERROR";
		}
		else if (_eType == Type::eWarn)
		{
			strType += "WARN";
		}
		else
		{
			strType += "UNKNOWN";
		}

		return strType;
	}

	void Set(const Type _eType, const char* _pFileName, const unsigned int _nLine, const char* _pMessage, ...)
	{
		std::string strMessage = "";
		
		strMessage += " [Time] " + VarUtils::GetTime();
		strMessage += " [Type] " + ConvertTypeToString(_eType);
		strMessage += " [File] " + (nullptr != _pFileName ? std::string(_pFileName) : "");
		strMessage += " [Line] " + std::to_string(_nLine);

		va_list pArgs;
		va_start(pArgs, _pMessage);
		strMessage += " [Log] " + VarUtils::GetString(_pMessage, pArgs);
		va_end(pArgs);

		unsigned short logIndex = static_cast<unsigned short>(LogStorage::m_vLogMessage.size());
		if (logIndex >= LogStorage::m_nMaxCount)
		{
			Handler::Clear();
			logIndex = 0;
		}
		LogStorage::m_vLogMessage.push_back(strMessage);

		if ((_eType == Type::eInfo) 
			|| (_eType == Type::eError)
			|| (_eType == Type::eWarn))
		{
			LogStorage::m_mLogType[_eType].push_back(logIndex);
		}
	}

	const std::vector<std::string> Get(const Type _eType)
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

	namespace Handler
	{
		void Init(const unsigned short _nMaxCount)
		{
			LogStorage::m_nMaxCount = _nMaxCount;
			LogStorage::m_vLogMessage.reserve(_nMaxCount);
		}

		void Clear()
		{
			LogStorage::m_vLogMessage.clear();
			LogStorage::m_mLogType.clear();
		}

		void Print(const Type _eType)
		{
			const auto vLogMessage = Get(_eType);

			for (auto logMessage : vLogMessage)
			{
				printf("%s\n", logMessage.c_str());
			}
		}
	}
}