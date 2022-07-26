#pragma once
#include <vector>
#include "Card.h"

typedef std::vector<Card> CardDeck;


class Cards
{
public:

	CardDeck cards;

	static CardDeck generateFullDeck();

	void drawCards(CardDeck& deck, int cardCount);
	size_t findByID(size_t ID);
	size_t findCardBySymbol(Card::Symbol symbol, Card::Figure figure);

};

