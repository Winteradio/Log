#ifndef __LOG_UTILS_H__
#define __LOG_UTILS_H__

#include <string>
#include <cstdint>
#include <memory>

namespace Log
{
	namespace Enum
	{
		enum eType : uint8_t;
		enum eLevel : uint8_t;
	}

	struct MetaData;

	namespace Utils
	{
		std::string ConvertToString(const uint64_t _uValue, const size_t _sizeValue);
		std::string ConvertToString(const int64_t _sValue, const size_t _sizeValue);
		std::string ConvertToString(const float _fValue);
		std::string ConvertToString(const double _dValue);
		std::string ConvertToString(const void* _pVoid);
		std::string ConvertToString(const bool _bValue);
		
		std::string GetTime();
		std::string GetType(const Enum::eType _eType);
		std::string GetDetails(const uint8_t _eLevel, const MetaData& _rMetaData);
	};
};

#endif // __LOG_UTILS_H__