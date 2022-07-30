#pragma once
#include "includes.h"

class Player
{
public:

	CardDeck cards;

	// dobierz karty
	void drawCards(CardDeck& deck, int cardCount);

	size_t findCardByID(size_t ID);
	size_t findCardBySymbol(Card::Symbol symbol, Card::Figure figure);
	size_t findCard(Card card);

	void printCards();
	void printCoveredCards();

	Player() {}
	//Player(const Player& other) //copy constructor

private:

	void printUpperOfCards();
	void printBottomOfCards();
};

 