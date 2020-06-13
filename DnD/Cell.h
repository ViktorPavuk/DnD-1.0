#pragma once
#include "Monster.h"
#include "Weapon.h"

class Cell
{

public:
	Weapon* Weapon;
	Monster* Monster;
	bool visited;
};

