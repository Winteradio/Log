#include <iostream>
#include <Log.h>

#ifdef _WIN32

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    Log::Info(" Windows ");
#elif __linux__
int main()
{
    Log::Info(" Linux ");
#endif
    Log::Info(" Hello World! ");
    Log::Warn(" This Log Status is Warn ");
    Log::Error(" This Log Status is Error ");

    Log::Print();

    return 0;
}