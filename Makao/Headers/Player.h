#pragma once
#include "includes.h"

class Player
{
public:

	CardDeck cards;

	void drawCards(CardDeck& deck, int cardCount);

	size_t findCardByID(size_t ID);
	size_t findCardBySymbol(Card::Symbol symbol, Card::Figure figure);

};

 