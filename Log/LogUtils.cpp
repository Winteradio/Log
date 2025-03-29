#include "LogUtils.h"

#include "LogConstants.h"

namespace Log
{
	std::string CheckNumofDigits(int value, int numDigits)
    {
        std::string numString = std::to_string(value);

        while(numString.length() < numDigits)
        {
            numString = "0" + numString;
        }

        return numString;
    }

	namespace Utils
	{
		std::string ConvertToString(const uint64_t _uValue, const size_t _valueSize)
		{
			std::string intValue;

			intValue = "[I/US/" + std::to_string(_valueSize) +"]";
			intValue += " ";
			intValue += std::to_string(_uValue);

			return intValue;
		};

		std::string ConvertToString(const int64_t _sValue, const size_t _valueSize)
		{
			std::string intValue;

			intValue = "[I/S/" + std::to_string(_valueSize) +"]";
			intValue += " ";
			intValue += std::to_string(_sValue);

			return intValue;
		};

		std::string ConvertToString(const void* _pVoid)
		{
			std::string pointerValue;

			pointerValue = "[P]";
			pointerValue += " ";
			pointerValue += std::to_string(
				reinterpret_cast<std::uintptr_t>(_pVoid)
			);

			return pointerValue;
		}

		std::string ConvertToString(const float _fValue)
		{
			std::string floatValue;
			floatValue = "[F]";
			floatValue += " ";
			floatValue += std::to_string(_fValue);

			return floatValue;
		}

		std::string ConvertToString(const double _dValue)
		{
			std::string doubleValue;
			doubleValue = "[DF]";
			doubleValue += " ";
			doubleValue += std::to_string(_dValue);

			return doubleValue;
		}

		std::string ConvertToString(const bool _bValue)
		{
			std::string booleanValue;
			booleanValue = "[B]";
			booleanValue += " ";
			booleanValue += std::string(_bValue ? "Y" : "N");

			return booleanValue;
		}


		std::string GetTime()
		{
			std::string strTime;
#ifdef PLATFORM_WINDOWS
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);

			strTime += Log::CheckNumofDigits(sysTime.wHour, 2) + ":";
			strTime += Log::CheckNumofDigits(sysTime.wMinute, 2) + ":";
			strTime += Log::CheckNumofDigits(sysTime.wSecond, 2) + ":";
			strTime += Log::CheckNumofDigits(sysTime.wMilliseconds, 2);
#elif PLATFORM_LINUX
			
#endif
			return strTime;
		}

		std::string GetType(const Enum::eType _eType)
		{
			std::string strType;

			if (_eType == Enum::eType_None)
			{
				strType = "NONE";
			}
			else if (_eType == Enum::eType_Info)
			{
				strType += "INFO";
			}
			else if (_eType == Enum::eType_Error)
			{
				strType += "ERROR";
			}
			else if (_eType == Enum::eType_Warn)
			{
				strType += "WARN";
			}
			else
			{
				strType += "..";
			}

			return strType;
		}

		std::string GetDetails(const uint8_t _eLevel, const MetaData& _rMetaData)
		{
			std::string strDetail;

			if (Enum::eLevel_None != (_eLevel & Enum::eLevel_Type))
			{
				strDetail += "[Type] " + GetType(_rMetaData.eType);
				strDetail += " ";
			}

			if (Enum::eLevel_None != (_eLevel & Enum::eLevel_Time))
			{
				strDetail += "[Time] " + GetTime();
				strDetail += " ";
			}

			if (Enum::eLevel_None != (_eLevel & Enum::eLevel_File))
			{
				strDetail += "[File] " + _rMetaData.strFileName;
				strDetail += " ";
			}

			if (Enum::eLevel_None != (_eLevel & Enum::eLevel_Func))
			{
				strDetail += "[Func] " + _rMetaData.strFuncName;
				strDetail += " ";
			}

			if (Enum::eLevel_None != (_eLevel & Enum::eLevel_Line))
			{
				strDetail += "[Line] " + _rMetaData.strLine;
				strDetail += " ";
			}

			return strDetail;
		}
	}
}
