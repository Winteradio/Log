#ifndef __LOG_CONSTANTS_H__
#define __LOG_CONSTANTS_H__

#include <cstdint>
#include <string>

namespace Log
{
	namespace Enum
	{
		enum eType : uint8_t
		{
			eType_None		= 0b0000001,
			eType_Info		= 0b0000010,
			eType_Error		= 0b0000100,
			eType_Warn		= 0b0001000,
			eType_Max		= 0b0001111,
		};

		enum eMode : uint8_t
		{
			eMode_None 		= 0b00000000,
			eMode_Print 	= 0b00000001,
			eMode_Save 		= 0b00000010,
			eMode_Max 		= 0b00000011,
		};

		enum eLevel : uint8_t
		{
			eLevel_None 	= 0b00000000,
			eLevel_Type		= 0b00000001,
			eLevel_Time 	= 0b00000010,
			eLevel_File 	= 0b00000100,
			eLevel_Func		= 0b00001000,
			eLevel_Line 	= 0b00010000,
			eLevel_Max 		= 0b00011111,
		};
	};

	struct MetaData
	{
		Enum::eType eType;
		std::string strFileName;
		std::string strFuncName;
		std::string strLine;

		MetaData()
			: eType(Enum::eType_None)
			, strFileName()
			, strFuncName()
			, strLine()
		{}

		MetaData(const Enum::eType _eType, const char* _pFileName, const char* _pFuncName, const unsigned int _nLine)
			: eType(_eType)
		{
			strFileName = (_pFileName != nullptr) ? std::string(_pFileName) : std::string("");
			strFuncName = (_pFuncName != nullptr) ? std::string(_pFuncName) : std::string("");
			strLine = std::to_string(_nLine);
		}

		MetaData(const MetaData& _rhs)
			: eType(_rhs.eType)
			, strFileName(_rhs.strFileName)
			, strFuncName(_rhs.strFuncName)
			, strLine(_rhs.strLine)
		{}
	};

	struct Entry
	{	
		MetaData tMetaData;
		std::string strMessage;

		Entry()
			: tMetaData()
			, strMessage()
		{}

		Entry(const Entry& _rhs)
			: tMetaData(_rhs.tMetaData)
			, strMessage(_rhs.strMessage)
		{}

		Entry(const MetaData& _MetaData, const std::string& _strMessage)
			: tMetaData(_MetaData)
			, strMessage(_strMessage)
		{}
	};
};

#endif // __LOG_CONSTANTS_H__