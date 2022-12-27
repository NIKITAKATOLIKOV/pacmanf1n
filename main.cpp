#include "game.h"
#ifdef WIN32
#include "windows.h"
#endif

int main()
{
#ifdef WIN32
    ShowWindow(GetConsoleWindow(), SW_HIDE); //убирает консоль
#endif
    Game game;
    game.Menu();
    return 0;
}