#include "Weapon.h"


std::string Weapon::GetStats()
{
	return Name + " (+" + std::to_string(Damage) + " attack power)";
}