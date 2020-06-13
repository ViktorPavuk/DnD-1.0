#pragma once
#include <string>
#include "Player.h"

class Monster
{
public:
	std::string Name;
	int HealthPoints;

	bool ReceiveDamage(int amount);
	std::string GetHPFormatted();
};

