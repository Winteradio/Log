#include "LogUtils.h"

#include "LogConstants.h"

#include <chrono>
#include <iomanip>
#include <sstream>

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

			std::stringstream pointerStream;
            pointerStream << "0x" << std::hex << std::uppercase << _pVoid;

			pointerValue += pointerStream.str();

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
			auto now = std::chrono::system_clock::now();
			auto time = std::chrono::system_clock::to_time_t(now);
				
			std::stringstream timeStream;
			timeStream << std::put_time(std::localtime(&time), "%H:%M:%S"); // 밀리초는 추가 구현 필요
			return timeStream.str();
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
