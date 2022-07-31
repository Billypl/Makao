#pragma once
#include "includes.h"

class Player
{
public:

	CardDeck cards;
	bool isBot;

	// dobierz karty
	void drawCards(CardDeck& deck, int cardCount);

	size_t findCardByID(size_t ID);
	size_t findCardBySymbol(Card::Symbol symbol, Card::Figure figure);
	size_t findCard(Card card);

	void printCards();
	void printCoveredCards();
	bool didWin();

	Player();

private:

	void printUpperOfCards();
	void printBottomOfCards();
};

 