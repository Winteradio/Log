#ifndef __LOG_HANDLER_H__
#define __LOG_HANDLER_H__

#include <memory>

namespace Log
{
	struct Entry;
	class Manager;

	class Handler
	{
		public :
			Handler() = delete;
			Handler(std::weak_ptr<Manager> _wpManager);
			virtual ~Handler();

		public :
			virtual void Send(const Entry& _rEntry) = 0;
			void Init(const uint8_t _eMode, const uint8_t _eLevel);
			const uint8_t GetMode();
			const uint8_t GetLevel();

		protected :
			uint8_t m_eMode;
			uint8_t m_eLevel;
			std::weak_ptr<Manager> m_wpManager;
	};
};

#endif // __LOG_EVENT_QUEUE_H__