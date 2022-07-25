#pragma once
#include <vector>
#include "Card.h"

typedef std::vector<Card> CardDeck;


class Cards
{
public:

	CardDeck cards;

	static CardDeck generateDeck();

	void populateRandom(CardDeck& cards);
	size_t findByID(size_t ID);
	size_t findByCardSymbols(Card::Symbol symbol, Card::Figure figure);

};

