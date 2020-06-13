#pragma once
#include <string>
#include "Weapon.h"
#include "Monster.h"

class Player
{
public:
	Player(std::string name, int position, int experience, Weapon* weapon);

	std::string Name;
	int CurrentPosition;
	int ExperiencePoints;
	std::string Level;
	Weapon* EquippedWeapon;

	std::tuple<int, std::string> PerformAttack();
	void ReceiveXP(int amount);
	bool CheckNewWeapon(Weapon* weapon);
	std::string GetPlayerStats();
};

