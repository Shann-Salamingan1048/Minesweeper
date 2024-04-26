
#include <iostream>
#include "Game.h"
// to show console
//int main()
// Project Properties : Linker > SubSystem >  Console(/ SUBSYSTEM:CONSOLE)
int WinMain() // use WinMain() to not show console and change the 
// Project Properties: Linker > SubSystem, from Console(/SUBSYSTEM:CONSOLE) to Windows(/SUBSYSTEM:WINDOWS)
{
	
	Game game;
	
	while (game.isRunning())
	{
	
		game.update();
		game.render();
	}
	return 0;
}