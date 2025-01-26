#ifndef __LOG_MESSAGE_H__
#define __LOG_MESSAGE_H__

#include <string>
#include <cstdint>
#include <memory>

#include "LogConstants.h"

namespace Log
{
	class Handler;

	class Message
	{
		public :
			Message();
			Message(const Message& _rhs);
			explicit Message(const MetaData& _MetaData, std::weak_ptr<Handler> _spHandler);
			Message(Message&& _rhs) noexcept;
			virtual ~Message();

			Message& operator=(const Message& _rhs);
			Message& operator=(Message&& _rhs) noexcept;

			Message& operator<<(const Message& _message);
			Message& operator<<(Message&& _message);
			Message& operator<<(const std::string& _string);
			Message& operator<<(const bool _boolean);

			Message& operator<<(const uint8_t _uint8);
			Message& operator<<(const uint16_t _uint16);
			Message& operator<<(const uint32_t _uint32);
			Message& operator<<(const uint64_t _uint64);

			Message& operator<<(const int8_t _sint8);
			Message& operator<<(const int16_t _sint16);
			Message& operator<<(const int32_t _sint32);
			Message& operator<<(const int64_t _sin64);

			Message& operator<<(const float _float);
			Message& operator<<(const double _double);

			Message& operator<<(const void* _pVoid);
			Message& operator<<(const char* _pChar);

		public :
			const std::string Get();

		private :
			MetaData m_tMetaData;
			std::string m_strMessage;
			std::weak_ptr<Handler> m_wpHandler;
	};
};

#endif // __LOG_MESSAGE_H__