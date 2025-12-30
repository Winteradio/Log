#include "LogManager.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace Log
{
	Manager::Manager()
		: m_LogMessage() 
		, m_TypeIndex()
		, m_nMaxCount(1024)
	{}

	Manager::~Manager()
	{}

	void Manager::Init(const unsigned short _nMaxCount)
	{
		m_nMaxCount = _nMaxCount;

		if ((m_nMaxCount > m_LogMessage.size()) ||
			(m_nMaxCount > m_LogMessage.capacity()))
		{
			m_LogMessage.reserve(m_nMaxCount);
		}
		else
		{
			Clear();
		}
	}

	void Manager::SetLog(const Enum::eType _eType, const std::string& _strMessage)
	{
		if (_eType == Enum::eType_Max)
		{
			printf("[LOG-ERROR] Failed to set log, the log type is invalid\n");
			return;
		}

		if (m_LogMessage.size() >= m_nMaxCount)
		{
			Clear();
		}

		const size_t index = m_LogMessage.size();
		m_LogMessage.push_back(std::move(_strMessage));
		m_TypeIndex[_eType].push_back(index);
	}

	const Manager::MessageList Manager::GetLogs(const uint8_t _eType)
	{
		IndexList vTotalIndex;

		for (size_t index = 0; index < m_TypeIndex.size(); index++)
		{
			if (Enum::eType_None != (_eType & (static_cast<uint8_t>(index))))
			{
				const auto& vIndexList = m_TypeIndex[index];
				vTotalIndex.insert(vTotalIndex.end(), vIndexList.begin(), vIndexList.end());
			}
		}

		std::sort(vTotalIndex.begin(), vTotalIndex.end());

		MessageList vMessageList;
		vMessageList.reserve(vTotalIndex.size());

		for (const auto& index : vTotalIndex)
		{
			vMessageList.push_back(m_LogMessage[index]);
		}

		return vMessageList;
	}

	void Manager::Print(const uint8_t _eType)
	{
		const MessageList messageList = GetLogs(_eType);
		for (const auto& strMessage : messageList)
		{
			printf("%s\n", strMessage);
		}
	}

	void Manager::Clear()
	{
		m_LogMessage.clear();

		for (auto& indexList : m_TypeIndex)
		{
			indexList.clear();
		}
	}
}