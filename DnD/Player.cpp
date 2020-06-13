#include "Player.h"
#include "Core.h"

Player::Player(std::string name, int position, int experience, Weapon* weapon)
{
	Name = name;
	CurrentPosition = position;
	ExperiencePoints = experience;
	EquippedWeapon = weapon;
	Level = "";
}

void Player::ReceiveXP(int amount)
{
	if (amount <= 0)
		return;

	ExperiencePoints += amount;
}

std::tuple<int, std::string> Player::PerformAttack()
{
	int weaponDamage = 0;

	if (EquippedWeapon)
		weaponDamage = EquippedWeapon->Damage;

	if (ExperiencePoints >= 5)
		weaponDamage++;
	if (ExperiencePoints >= 10)
		weaponDamage++;

	int rolled = Core::RollDice();
	int totalDamage = rolled + weaponDamage;

	std::string formattedDamage = std::to_string(totalDamage) + " (rolled " + std::to_string(rolled) + " + " + std::to_string(weaponDamage) + " weapon attack)";

	return std::make_tuple(totalDamage, formattedDamage);
}

bool Player::CheckNewWeapon(Weapon* weapon)
{
	if (EquippedWeapon == nullptr || EquippedWeapon->Damage < weapon->Damage)
	{
		EquippedWeapon = weapon;
		return true;
	}

	return false;
}

std::string Player::GetPlayerStats()
{	
	if (ExperiencePoints >= 10)
		Level = " (+2 attack power)";
	else if (ExperiencePoints >=5)
		Level = " (+1 attack power)";

	std::string stats;
	stats.append(Name + " Position: ").append(std::to_string(CurrentPosition + 1)).append("\n");
	stats.append(Name + " XP: ").append(std::to_string(ExperiencePoints)).append(Level).append("\n");
	stats.append(Name + " Weapon: ").append(EquippedWeapon->GetStats() + "\n");
	return stats;
}
