#include "LogDefaultHandler.h"

#include "LogConstants.h"
#include "LogManager.h"

#include "LogUtils.h"

#include <iostream>

namespace Log
{
	DefaultHandler::DefaultHandler(std::weak_ptr<Manager> _wpManager)
		: Handler(_wpManager)
	{}

	void DefaultHandler::Send(const Entry& _rEntry)
	{
		const uint8_t eMode = GetMode();
		const uint8_t eLevel = GetLevel();

		std::string strLog = Utils::GetDetails(eLevel, _rEntry.tMetaData);
		strLog += "[Log] " + _rEntry.strMessage;

		if (Enum::eMode_None != (eMode & Enum::eMode_Print))
		{
			std::cout << strLog << std::endl;
		}

		if (Enum::eMode_None != (eMode & Enum::eMode_Save))
		{
			if (std::shared_ptr<Manager> spManager = m_wpManager.lock())
			{
				spManager->SetLog(_rEntry.tMetaData.eType, strLog);
			}
		}
	}
}