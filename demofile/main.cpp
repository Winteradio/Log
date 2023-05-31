#include <iostream>
#include <Log.h>

#ifdef _WIN32
int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
#elif __linux__
int main()
#endif
{
    Log::Info(" Hello World! ");
    Log::Warn(" This Log Status is Warn ");
    Log::Error(" This Log Status is Error ");

    for ( auto Message : Log::GetMessage() )
    {
        std::cout << Message << std::endl;
    }

    system("pause");

    return 0;
}