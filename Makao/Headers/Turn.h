#pragma once
#include "Card.h"

class Turn
{
public:

	int currentPlayer;
	bool isCardPlaced;
	bool saidMakao;
	bool hasDrawnCard;
	int drawAmount;
	Card lastPlacedCard;

	// returns current bot option number, then increments it
	// something like botPickedOptions++
	int incrementBotPickedNumber();

	void nextTurn();
	Turn();
private:

	int botPickedOption;
	void incrementCurrentPlayerNumber();
};

