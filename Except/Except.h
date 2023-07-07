#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include "Timer.h"

#include <exception>
#include <cstdarg>

class Except : public std::exception
{
    public :
        Except();
        Except( const char* Str, ... );
        virtual ~Except();

    public :
        const char* what() const noexcept override;
        const char* GetMessage();

    private :
        std::string m_Message;
};

#endif // __EXCEPT_H__