#include "VarUtils.h"

#include <windows.h>

namespace VarUtils
{
    std::string VarUtils::GetString(const char* _pMessage, va_list _pArg)
    {
        if (nullptr == _pMessage)
        {
            return std::string();
        }

        short nLength = vsnprintf(nullptr, 0, _pMessage, _pArg);
        if (nLength < 0)
        {
            printf("[VARUTILS] Formatting error \n");
            return std::string();
        }

        std::string strMessage(nLength, '\0');
        vsnprintf(strMessage.data(), strMessage.size() + 1, _pMessage, _pArg);

        return strMessage;
    }

    std::string CheckNumofDigits(int value, int numDigits)
    {
        std::string numString = std::to_string(value);

        while(numString.length() < numDigits)
        {
            numString = "0" + numString;
        }

        return numString;
    }

    std::string GetTime()
    {
        SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);

        std::string currentTime;

        currentTime += CheckNumofDigits(sysTime.wHour, 2) + ":";
        currentTime += CheckNumofDigits(sysTime.wMinute, 2) + ":";
        currentTime += CheckNumofDigits(sysTime.wSecond, 2) + ":";
        currentTime += CheckNumofDigits(sysTime.wMilliseconds, 2);

        return currentTime;
    }
}