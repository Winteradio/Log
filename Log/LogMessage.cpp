#include "LogMessage.h"

#include "LogConstants.h"
#include "LogHandler.h"
#include "LogUtils.h"

#include <iostream>

namespace Log
{
	Message::Message()
		: m_tMetaData()
		, m_strMessage()
	{}

	Message::Message(const Message& _rhs)
		: m_tMetaData(_rhs.m_tMetaData)
		, m_wpHandler(_rhs.m_wpHandler)
		, m_strMessage(_rhs.m_strMessage)
	{
		m_strMessage = _rhs.m_strMessage;
	}

	Message::Message(const MetaData& _MetaData, std::weak_ptr<Handler> _wpHandler)
		: m_tMetaData(_MetaData)
		, m_wpHandler(_wpHandler)
		, m_strMessage()
	{}

	Message::Message(Message&& _rhs) noexcept
		: m_tMetaData(_rhs.m_tMetaData)
		, m_strMessage(std::move(_rhs.m_strMessage))
		, m_wpHandler(std::move(_rhs.m_wpHandler))
	{}

	Message::~Message()
	{
		if (m_strMessage.empty())
		{
			return;
		}

		if (std::shared_ptr<Handler> spHandler = m_wpHandler.lock())
		{
			spHandler->Send(Entry(m_tMetaData, Get()));
		}
	}

	Message& Message::operator=(const Message& _rhs)
	{
		if (this != &_rhs)
		{
			this->m_tMetaData = _rhs.m_tMetaData;
			this->m_strMessage = _rhs.m_strMessage;
			this->m_wpHandler = _rhs.m_wpHandler;
		}

		return *this;
	}

	Message& Message::operator=(Message&& _rhs) noexcept
	{
		this->m_tMetaData = _rhs.m_tMetaData;
		this->m_strMessage = std::move(_rhs.m_strMessage);
		this->m_wpHandler = std::move(_rhs.m_wpHandler);
	
		_rhs.m_strMessage.clear();

		return *this;
	}

	Message& Message::operator<<(const Message& _message)
	{
		m_strMessage += _message.m_strMessage;

		return *this;
	}

	Message& Message::operator<<(Message&& _message)
	{
		m_strMessage += _message.m_strMessage;

		return *this;
	}

	Message& Message::operator<<(const std::string& _string)
	{
		m_strMessage += _string;

		return *this;
	}

	Message& Message::operator<<(const bool _boolean)
	{
		m_strMessage += Utils::ConvertToString(_boolean);

		return *this;
	}

	Message& Message::operator<<(const uint8_t _uing8)
	{
		m_strMessage += Utils::ConvertToString(static_cast<uint64_t>(_uing8), sizeof(_uing8));

		return *this;
	}

	Message& Message::operator<<(const uint16_t _uint16)
	{
		m_strMessage += Utils::ConvertToString(static_cast<uint64_t>(_uint16), sizeof(_uint16));

		return *this;
	}

	Message& Message::operator<<(const uint32_t _uint32)
	{
		m_strMessage += Utils::ConvertToString(static_cast<uint64_t>(_uint32), sizeof(_uint32));

		return *this;
	}

	Message& Message::operator<<(const uint64_t _uint64)
	{
		m_strMessage += Utils::ConvertToString(static_cast<uint64_t>(_uint64), sizeof(_uint64));

		return *this;
	}

	Message& Message::operator<<(const int8_t _sint8)
	{
		m_strMessage += Utils::ConvertToString(static_cast<int64_t>(_sint8), sizeof(_sint8));

		return *this;
	}

	Message& Message::operator<<(const int16_t _sint16)
	{
		m_strMessage += Utils::ConvertToString(static_cast<int64_t>(_sint16), sizeof(_sint16));

		return *this;
	}

	Message& Message::operator<<(const int32_t _sint32)
	{
		m_strMessage += Utils::ConvertToString(static_cast<int64_t>(_sint32), sizeof(_sint32));

		return *this;
	}

	Message& Message::operator<<(const int64_t _sint64)
	{
		m_strMessage += Utils::ConvertToString(static_cast<int64_t>(_sint64), sizeof(_sint64));

		return *this;
	}

	Message& Message::operator<<(const float _float)
	{
		m_strMessage += Utils::ConvertToString(_float);

		return *this;
	}

	Message& Message::operator<<(const double _double)
	{
		m_strMessage += Utils::ConvertToString(_double);

		return *this;
	}

	Message& Message::operator<<(const void* _pVoid)
	{
		m_strMessage += Utils::ConvertToString(_pVoid);

		return *this;
	}

	Message& Message::operator<<(const char* _pChar)
	{
		m_strMessage += std::string(_pChar);

		return *this;
	}

	const std::string& Message::Get() const
	{
		return m_strMessage;
	}
};