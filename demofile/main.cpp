#include "Log.h"
#include "Except.h"

void Example()
{
    LOGINFO(" Hello World! ");
    LOGWARN(" Comming Exception");    
    
    while (true)
    {
        static int value = 0;
        value++;
        LOGINFO(" Count : %d", value);

        if (value > 50000)
        {
            break;
        }
    }

    throw Except("Something went wrong! %d ", 999 );

    LOGINFO(" After Exception");
}

#ifdef _WIN32
    #include <windows.h>
    #pragma comment(linker, "/entry:WinMainCRTStartup")
    #pragma comment(linker, "/subsystem:console")

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    LOGINFO(" Platform is Windows");
#else
int main()
{
    Log::Info(" Linux ");
#endif
    try
    {
        Example();
    }
    catch (const Except& e)
    {
        LOGERROR(e.what());
    }

    Log::Handler::Print();

    Log::Handler::Clear();
    LOGINFO(" Resume Log ");
    Log::Handler::Print();

    system("pause");

    return 0;
}
