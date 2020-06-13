#include "Core.h"

#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "Windows.h"
#include "DataSetuper.h"
#include "Weapon.h"

using namespace std;

struct Actions
{
public:
	void FormatMessage(std::string message)
	{
		cout << "------------------------------------------------------" << endl;
		cout << message;
		cout << "------------------------------------------------------" << endl << endl;
	}

	void Move(int distance, int* currentPosition)
	{
		int lastPosition = *currentPosition;
		*currentPosition += distance;
		*currentPosition = fmin(DataSetuper::DragonPosition, *currentPosition);
		int movedFor = *currentPosition - lastPosition;

		string message = "Hero moved for " + std::to_string(movedFor) + " positions forward \n";
		FormatMessage(message);
	}

	bool Dismount(Cell* cell, Player* player)
	{
		if (cell->visited)
		{
			string message = "There is nothing left for " + player->Name + " to do here \n";
			FormatMessage(message);
			return true;
		}

		cell->visited = true;

		if (cell->Monster != nullptr && player->CurrentPosition == DataSetuper::DragonPosition)
		{
			bool victorious = FightWithDragon(cell->Monster, player);
			cell->Monster = nullptr;

			return victorious;
		}

		if (cell->Monster != nullptr)
		{
			bool victorious = FightWithMonster(cell->Monster, player);
			cell->Monster = nullptr;

			return victorious;
		}

		if (cell->Weapon != nullptr)
		{
			TryEquipWeapon(cell->Weapon, player);
			cell->Weapon = nullptr;
		}
		else
		{
			string message = "There is nothing for " + player->Name + " to do, so " + player->Name + " reflect upon his adventures thus far. \n" + player->Name + " take the time to train and enchance his reflexes \n";
			FormatMessage(message);

			message = player->Name + " received " + std::to_string(1) + " experience points \n";
			FormatMessage(message);

			player->ReceiveXP(1);
		}

		return true;
	}

private:
	bool FightWithMonster(Monster* monster, Player* player)
	{
		std::tuple<int, std::string> attack = player->PerformAttack();
		int totalDamage = std::get<0>(attack);
		std::string formattedDamage = std::get<1>(attack);
		std::string monsterHP = monster->GetHPFormatted();

		bool killedMonster = monster->ReceiveDamage(totalDamage);

		string message = "While looking around, " + player->Name + " stumbled upon " + monster->Name + monsterHP + " and prepared to fight for his life \n";
		FormatMessage(message);

		message = player->Name + " attacked ferocious " + monster->Name + " and dealt " + formattedDamage + " damage with his " + player->EquippedWeapon->Name + "\n"
			+ monster->Name + " has " + std::to_string(monster->HealthPoints) + " health points left \n";
		FormatMessage(message);

		if (killedMonster)
		{
			message = player->Name + " killed a " + monster->Name + "\n";
			FormatMessage(message);

			message = player->Name + " received " + std::to_string(2) + " experience points \n";
			FormatMessage(message);

			player->ReceiveXP(2);
			return true;
		}
		else
		{
			message = player->Name + " failed to kill " + monster->Name + " and was consumed \n";
			FormatMessage(message);

			return false;
		}
	}

	bool FightWithDragon(Monster* monster, Player* player)
	{
		bool passedXPCheck = player->ExperiencePoints >= 5;
		std::string message;
		std::string monsterHP = monster->GetHPFormatted();

		message = "While looking around, " + player->Name + " stumbled upon " + monster->Name + monsterHP + " and prepared to fight for his life \n";
		FormatMessage(message);

		if (!passedXPCheck)
		{
			message = std::string("Alas, the dragon's eyes stare at " + player->Name + " and places him under his spell. " + player->Name + " tries to move but fail to do so and find himself torched by the dragon's fire.")
				+ " If only " + player->Name + " had read guides on this game, he would have seen it coming. \n";
			FormatMessage(message);
			return false;
		}

		std::tuple<int, std::string> attack = player->PerformAttack();
		int totalDamage = std::get<0>(attack);
		std::string formattedDamage = std::get<1>(attack);

		bool killedMonster = monster->ReceiveDamage(totalDamage);

		message = player->Name + " attacked ferocious " + monster->Name + monsterHP + " and dealt " + formattedDamage + " damage with his " + player->EquippedWeapon->Name + "\n"
			+ monster->Name + " has " + std::to_string(monster->HealthPoints) + " health points left \n";
		FormatMessage(message);

		if (killedMonster)
		{
			message = player->Name + " ,due to his cunning and experience, defeated the deadly dragon. In the end of his journey, he finally found the Helm of Domination. \n";
			FormatMessage(message);
			
			if (player->EquippedWeapon->Name == "Frostmourne")
			{
				string input;
				message = "Arthas looks at his glowing runed sword. His attention turns to the fallen dragon, there's one more thing he needs to do. He stops for a second to reflect. \nWhat is the name of the dragon? \n";
				FormatMessage(message);
				cin >> input;
				message = "Raise, " + input + "! Raise and serve your master! \n";
				FormatMessage(message);
				if (input == "Sapphiron")
				{
					message = "An earth shattering roar pierced the air as the frost wyrm rose from the dead. He will serve, he must serve! \nThe rest is history. \n";
					FormatMessage(message);
				}
				else
				{
					message = "Despite Arthas' huge effort, nothing happened. Perhaps he should have googled the dragon's name. \n";
					FormatMessage(message);
				}

			}

			return true;
		}
		else
		{
			message = player->Name + " failed to kill " + monster->Name + " and was torched by the dragon's fire. \n";
			FormatMessage(message);

			return false;
		}
	}

	void TryEquipWeapon(Weapon* weapon, Player* player)
	{
		std::string oldWeaponStats = player->EquippedWeapon->GetStats();
		std::string newWeaponStats = weapon->GetStats();
		std::string playerName = player->Name;

		bool equipped = player->CheckNewWeapon(weapon);

		std::string message;
		if (equipped)
		{
			message = "While looking around " + playerName + " found a new weapon, mighty " + newWeaponStats
				+ ". Seems like it would be nice to use it instead of his " + oldWeaponStats + "\n";
		}
		else
		{
			message = "While looking around, " + playerName + " found a new weapon, plain " + newWeaponStats + ". Unfortunatelly for " + weapon->Name + ", " + playerName + "'s " + oldWeaponStats + " is much more powerfull \n";
		}

		FormatMessage(message);
	}
};

bool Core::MainLoop(vector<Cell*> cells, Player* player)
{
	srand(time(0));

	Actions act;

	std::string introduction = "This is the story about " + player->Name + " and his epic quest for Helm of Domination. \n";
	act.FormatMessage(introduction);

	string input;

	while (true)
	{
		DisplayField(player->CurrentPosition);
		DisplayPlayerStats(player->GetPlayerStats());
		DisplayInputOptions();

		cin >> input;
		system("cls");

		if (input == "1")
		{
			int oldPosition = player->CurrentPosition;

			act.Move(RollDice(), &player->CurrentPosition);

			AnimateMovement(oldPosition, player->CurrentPosition);
		}
		else if (input == "2")
		{
			bool success = act.Dismount((cells.at(player->CurrentPosition)), player);

			if (!success)
			{
				return DisplayNewAdventureNotify();
			}
		}

		if (player->CurrentPosition == DataSetuper::DragonPosition)
		{
			act.Dismount((cells.at(player->CurrentPosition)), player);
			return DisplayNewAdventureNotify();
		}

	}
}

bool Core::DisplayNewAdventureNotify()
{
	std::string input;
	while (true)
	{
		cout << "Do you want to start new adventure?" << endl << "1) Yes" << endl << "2) No" << endl << endl;
		cin >> input;

		if (input == "1")
			return false;

		if (input == "2")
			exit(0);
	}
}

int Core::RollDice()
{
	srand(time(NULL));
	return 1 + rand() % 6;
}

void Core::DisplayField(int playerPosition)
{
	string field;
	for (int i = 0; i < 28; i++)
	{
		if (i == playerPosition)
		{
			field.append("P");
		}
		else if (i == DataSetuper::DragonPosition)
		{
			field.append("D");
		}
		else
		{
			field.append("*");
		}
	}

	cout << field << endl;
}

void Core::DisplayPlayerStats(string stats)
{
	cout << stats;
}

void Core::DisplayInputOptions()
{
	cout << endl;
	cout << "1) Travel to another space on the map" << endl;
	cout << "2) Dismount and exlore the current space" << endl << endl;
}

void Core::AnimateMovement(int startPosition, int endPosition)
{
	while (startPosition < endPosition)
	{
		DisplayField(startPosition);
		startPosition++;

		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

