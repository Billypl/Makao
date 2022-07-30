#pragma once
#include "Card.h"

class Turn
{
public:

	int currentPlayer;
	bool isCardPlaced;
	bool saidMakao;
	bool hasDrawedCard;

	void nextTurn();
	Turn();
private:

	void incrementCurrentPlayerNumber();
};

