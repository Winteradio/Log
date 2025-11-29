#ifndef __LOG_DEFAULT_HANDLER_H__
#define __LOG_DEFAULT_HANDLER_H__

#include "LogHandler.h"

namespace Log
{
	class DefaultHandler : public Handler
	{
		public :
			DefaultHandler() = delete;
			DefaultHandler(std::weak_ptr<Manager> _wpManager);

		public :
			void Send(const Entry& _rEntry) final;
	};
};

#endif // __LOG_DEFAULT_HANDELR_H__