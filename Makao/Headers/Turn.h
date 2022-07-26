#pragma once
#include "Card.h"

class Turn
{
public:

	int currentPlayer;
	bool isCardPlaced;
	bool isMakaoSaid;
	bool isCardDrawn;
	int drawAmount;
	Card lastPlacedCard;

	// returns current bot option number, then increments it
	// something like botPickedOptions++
	int incrementBotPickedNumber();
	void incrementCurrentPlayerNumber();
	void decrementCurrentPlayerNumber();

	void nextTurn();
	Turn();

private:

	int botPickedOption;
};

