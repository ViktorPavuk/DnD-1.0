#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Cell.h"
#include "Player.h"
#include <cmath>


class Core
{
public:
	bool MainLoop(std::vector<Cell*> cells, Player* player);

private:
	void DisplayField(int playerPosition);
	void DisplayPlayerStats(std::string stats);
	void DisplayInputOptions();
	void AnimateMovement(int startPosition, int endPosition);
	bool DisplayNewAdventureNotify();

public:
	static int RollDice();
};
