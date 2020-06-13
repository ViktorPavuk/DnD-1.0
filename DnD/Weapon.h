#pragma once
#include <string>

class Weapon
{
public:
	Weapon(std::string name, int damage)
	{
		Name = name;
		Damage = damage;
	}

	std::string GetStats();

	std::string Name;
	int Damage;
};

