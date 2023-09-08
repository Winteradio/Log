#include <iostream>
#include <LogProject/Log.h>
#include <windows.h>

void Example()
{
    Log::Info(" Hello World! ");
    throw Except("Something went wrong! %d ", 999 );

    Log::Warn(" The Stack is not escaped!! ");
}

#ifdef _WIN32
int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    Log::Info(" Windows ");
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
        Log::Error( e.what() );
    }

    Log::Print();

    return 0;
}