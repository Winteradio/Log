#include "Except.h"

Except::Except() : std::exception() {};

Except::Except( const char* Str, ... ) : std::exception()
{
    va_list pArg;
    va_start( pArg, Str );

    char Buff[MAX_LENGTH]; 
    Buff[0]='\0';
	vsprintf( Buff + strlen( Buff ), Str, pArg );

    va_end( pArg );
    m_Message = Buff;
}

Except::~Except() {}

const char* Except::what() const noexcept { return m_Message.c_str(); }