#pragma once
#include "Card.h"

class Turn
{
public:

	int currentPlayer;
	bool isCardPlaced;
	bool saidMakao;
	bool hasDrawedCard;

	// returns current bot option number, then increments it 
	int incrementBotPickedNumber();

	void nextTurn();
	Turn();
private:

	int botPickedOption;
	void incrementCurrentPlayerNumber();
};

