#include "Monster.h"
#include <cmath>

bool Monster::ReceiveDamage(int amount)
{
	HealthPoints = fmax(0, HealthPoints - amount);

	return HealthPoints <= 0;
}

std::string Monster::GetHPFormatted()
{
	return "(" + std::to_string(HealthPoints) + " health points)";
}