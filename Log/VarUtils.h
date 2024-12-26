#ifndef __VARUTILS_H__
#define __VARUTILS_H__

#include <string>
#include <stdarg.h>

namespace VarUtils
{
    std::string GetString(const char* _pMessage, va_list _pArg);
    std::string GetTime();
};

#endif // __VARUTILS_H__