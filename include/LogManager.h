#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include <array>
#include <string>
#include <vector>

#include "LogConstants.h"

namespace Log
{
	class Manager
	{
		private :
			using MessageList = std::vector<std::string>;
			using IndexList = std::vector<size_t>;
			using TypeIndexList = std::array<IndexList, static_cast<size_t>(Enum::eType_Max)>;

		public :
			Manager();
			~Manager();

		public :
			void Init(const unsigned short _nMaxCount);
			void SetLog(const Enum::eType _eType, const std::string& _strMessage);

			const MessageList GetLogs(const uint8_t _eType);

			void Print(const uint8_t _eType);
			void Clear();

		private :
			MessageList m_LogMessage;
			TypeIndexList m_TypeIndex;
			unsigned short m_nMaxCount;
	};
};

#endif // __LOG_MANAGER_H__