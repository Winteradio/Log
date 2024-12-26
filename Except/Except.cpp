#include "Except.h"
#include "VarUtils.h"

Except::Except() : std::exception() {};

Except::Except(const char* _pMessage, ...) : std::exception()
{
    va_list pArg;
    va_start(pArg, _pMessage);
    m_strMessage = VarUtils::GetString(_pMessage, pArg);
    va_end(pArg);
}

Except::~Except() {}

const char* Except::what() const noexcept 
{ 
    return m_strMessage.c_str(); 
}