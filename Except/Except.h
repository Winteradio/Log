#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include "Timer.h"

#ifndef _WIN32
#include <cstring>
#endif

#include <exception>
#include <cstdarg>

class Except : public std::exception
{
    public :
        Except();
        Except( const char* Str, ... );
        virtual ~Except();

    public :
        virtual const char* what() const noexcept override;

    private :
        std::string m_Message;
};

#endif // __EXCEPT_H__