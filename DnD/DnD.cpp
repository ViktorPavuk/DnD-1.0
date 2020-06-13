#include <iostream>
#include "Core.h"
#include "Player.h"
#include "Cell.h"
#include <array>
#include <ctime>
#include <windows.h>
#include "DataSetuper.h"

using namespace std;

int main()
{
	SetConsoleTitle(TEXT("Wrath of the King"));
	
	DataSetuper setup;
	Core coreGameplay = Core();
	Player* hero = nullptr;
	vector<Cell*> gameField;

	bool victory = false;

	while (!victory)
	{
		system("cls");

		hero = setup.SetupPlayer();
		gameField = setup.SetupNewField();

		victory = coreGameplay.MainLoop(gameField, hero);
	}
}



