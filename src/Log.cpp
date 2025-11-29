#include "Log.h"

#include "LogManager.h"

#include "LogDefaultHandler.h"

namespace Log
{
	std::shared_ptr<Handler> spDefaultHandler;
	std::shared_ptr<Manager> spLogManager;

	void Init(const unsigned short _nMaxCount, const uint8_t _eMode, const uint8_t _eLevel)
	{
		if (!spLogManager)
		{
			spLogManager = std::make_shared<Manager>();
			spLogManager->Init(_nMaxCount);
		}

		if (!spDefaultHandler)
		{
			spDefaultHandler = std::make_shared<DefaultHandler>(spLogManager);
			spDefaultHandler->Init(_eMode, _eLevel);
		}
	}

	void SetCount(const unsigned short _nMaxCount)
	{
		if (spLogManager)
		{
			spLogManager->Init(_nMaxCount);
		}
	}

	void SetMode(const uint8_t _eMode)
	{
		if (spDefaultHandler)
		{
			spDefaultHandler->Init(_eMode, spDefaultHandler->GetLevel());
		}
	}

	void SetLevel(const uint8_t _eLevel)
	{
		if (spDefaultHandler)
		{
			spDefaultHandler->Init(spDefaultHandler->GetMode(), _eLevel);
		}
	}

	void Print(const uint8_t _eType)
	{
		if (spLogManager)
		{
			spLogManager->Print(_eType);
		}
	}

	std::weak_ptr<Handler> GetHandler()
	{
		return spDefaultHandler;
	}
};