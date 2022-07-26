#include "../Headers/Cards.h"
#include "../Headers/includes.h"

using namespace std;

using enum Card::Figure;
using enum Card::Symbol;

using namespace std;

CardDeck Cards::generateFullDeck()
{
	CardDeck cards;
	for (auto const symbol : Card::symbols)
		for (auto const figure : Card::figures)
			cards.push_back(Card(symbol, figure));
	return cards;
}

void Cards::drawCards(CardDeck& deck, int cardCount)
{
	for (int i = 0; i < cardCount; i++)
	{
		int x = random::range(0, deck.size() - 1);
		this->cards.push_back(deck[x]);
		deck.erase(deck.begin() + x);
	}
}

size_t Cards::findByID(size_t ID)
{
	for (int i = 0; i < cards.size(); i++)
		if (cards[i].id == ID)
			return i;
	return -1;
}

size_t Cards::findCardBySymbol(Card::Symbol symbol, Card::Figure figure)
{
	for (int i = 0; i < cards.size(); i++)
		if (cards[i].symbol == symbol && cards[i].figure == figure)
			return i;
	return -1;
}