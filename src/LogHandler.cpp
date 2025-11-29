#include "LogHandler.h"

#include "LogConstants.h"

namespace Log
{
	Handler::Handler(std::weak_ptr<Manager> _wpManager)
		: m_eMode(static_cast<uint8_t>(Enum::eMode_None))
		, m_eLevel(static_cast<uint8_t>(Enum::eLevel_None))
		, m_wpManager(_wpManager)
	{}

	Handler::~Handler()
	{}

	void Handler::Init(const uint8_t _eMode, const uint8_t _eLevel)
	{
		m_eMode = _eMode;
		m_eLevel = _eLevel;
	}

	uint8_t Handler::GetMode()
	{
		return m_eMode;
	}

	uint8_t Handler::GetLevel()
	{
		return m_eLevel;
	}
}