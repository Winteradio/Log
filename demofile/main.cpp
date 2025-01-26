#include <windows.h>
#pragma comment(linker, "/entry:WinMainCRTStartup")
#pragma comment(linker, "/subsystem:console")

#include "Log.h"

void Example_Level()
{
	Log::SetLevel(Log::Enum::eLevel_Type | Log::Enum::eLevel_Time);
	LOG() << "Log None";

	Log::SetLevel(Log::Enum::eLevel_Type | Log::Enum::eLevel_Time | Log::Enum::eLevel_File);
	LOGINFO() << "Log Info";

	Log::SetLevel(Log::Enum::eLevel_Type | Log::Enum::eLevel_Time | Log::Enum::eLevel_File | Log::Enum::eLevel_Func);
	LOGWARN() << "Log Warn";

	Log::SetLevel(Log::Enum::eLevel_Type | Log::Enum::eLevel_Time | Log::Enum::eLevel_File | Log::Enum::eLevel_Func | Log::Enum::eLevel_Line);
	LOGERROR() << "Log Error";
}

void Example_Argument()
{
	Log::SetLevel(Log::Enum::eLevel_Type);
	Log::SetMode(Log::Enum::eMode_Print);
	bool _boolean = false;
	LOGINFO() << "Boolean " << _boolean;

	uint8_t _uint8 = 8;
	LOGINFO() << "Unsigned Int " << _uint8;

	uint16_t _uint16 = 16;
	LOGINFO() << "Unsigned Int " << _uint16;

	uint32_t _uint32 = 32;
	LOGINFO() << "Unsigned Int " << _uint32;

	uint64_t _uint64 = 64;
	LOGINFO() << "Unsigned Int " << _uint64;

	int8_t _sint8 = -8;
	LOGINFO() << "Signed Int " << _sint8;
	
	int16_t _sint16 = -16;
	LOGINFO() << "Signed Int " << _sint16;

	int32_t _sint32 = -32;
	LOGINFO() << "Signed Int " << _sint32;

	int64_t _sint64 = -64;
	LOGINFO() << "Signed Int " << _sint64;

	float _float = 0.01f;
	LOGINFO() << "Float " << _float;
	
	double _double = 0.01;
	LOGINFO() << "Double " << _double;

	void* _pValue = reinterpret_cast<void*>(new int(4));
	LOGINFO() << "Void Pointer " << _pValue;

	const char* _pChar = "Hello World!";
	LOGINFO() << "Char Pointer " << _pChar;
}

void Example_Time()
{
	Log::SetLevel(Log::Enum::eLevel_Time);
	while(true)
	{
		static int value = 0;
		if (value > 5000)
		{
			break;
		}

		value++;
		LOGINFO () << "Count " << value;
	}
}

void Example_Throw()
{
	throw EXCEPT(LOG() << "Something went wrong! : " << 999);
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	// Invalid Situation - The log must be initialized;
	LOG() << "Platform is Windows";

	// Initialize Log for directly priting and saving the log message
	// And the log handler print the type's string of the log's metadata
	Log::Init(1024, Log::Enum::eMode_Print | Log::Enum::eMode_Save, Log::Enum::eLevel_Type);
	LOG() << "Log Type";

	try
	{	
		Example_Level();
		Example_Argument();
		Example_Time();
		Example_Throw();
	}
	catch (Log::Message&& e)
	{
		LOG() << e.Get();
		Log::Print(Log::Enum::eType_None | Log::Enum::eType_Info);
	}

	system("pause");

	return 0;
}
