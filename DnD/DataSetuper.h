#pragma once
#include "Weapon.h"
#include "Monster.h"
#include "Cell.h"
#include "Player.h"
#include <vector>
#include <ctime>

class DataSetuper
{
	static const int WorldLength = 28;

	const int PlayerStartPosition = 0;

	Weapon* availableWeapons[5] = { new Weapon("Steel hammer", 3), new Weapon("Flail", 4), new Weapon("Broad Sword", 5), new Weapon("Ashbringer", 6), new Weapon("Frostmourne", 7) };
	std::string possibleMonsterNames[11] = { "Cavernscreamer", "Cryptghoul", "Dawnsnare", "The Evil Glob", "The Ugly Entity", "Bowelsnare", "Dreamwings", "Rottingling", "Venompaw", "The Cruel Monster", "Abysssnake" };

private:
	Weapon* GetWeapon(int index);
	Monster* GetRandomMonster();

public:
	static const int DragonPosition = WorldLength - 1;
	std::vector<Cell*> SetupNewField();
	Player* SetupPlayer();
};

