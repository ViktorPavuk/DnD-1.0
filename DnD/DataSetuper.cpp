#include "DataSetuper.h"

std::vector<Cell*> DataSetuper::SetupNewField()
{
	std::vector<Cell*> gameField;
	int monsters = 0;
	int weapons = 0;

	srand(time(NULL));

	for (int i = 0; i < WorldLength; i++)
		gameField.push_back(new Cell());

	gameField.at(0)->visited = true; // We can't explore the starting cell

	while (monsters < 14 || weapons < 5)
	{
		for (int i = 1; i < WorldLength; i++)
		{
			int type = rand() % 10;
			Cell* cellRef = gameField.at(i);
			if (i == DragonPosition && cellRef->Monster == nullptr)
			{
				Monster* dragon = new Monster();
				dragon->Name = "Dragon";
				dragon->HealthPoints = 10;

				cellRef->Monster = dragon;
			}
			else if (type == 0 && monsters < 14 && cellRef->Monster == nullptr && cellRef->Weapon == nullptr)
			{
				cellRef->Monster = GetRandomMonster();
				monsters++;
			}
			else if (type == 1 && weapons < 5 && cellRef->Monster == nullptr && cellRef->Weapon == nullptr)
			{
				cellRef->Weapon = GetWeapon(weapons);
				weapons++;
			}
		}
	}

	return gameField;
}

Player* DataSetuper::SetupPlayer()
{
	return new Player("Arthas", PlayerStartPosition, 0, new Weapon("Rusty Hammer", 0));
}

Weapon* DataSetuper::GetWeapon(int index)
{
	return availableWeapons[index];
}

Monster* DataSetuper::GetRandomMonster()
{
	Monster* m = new Monster();
	int nameIndex = rand() % 11;
	m->Name = possibleMonsterNames[nameIndex];
	m->HealthPoints = 3 + rand() % 5;

	return m;
}