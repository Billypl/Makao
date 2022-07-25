#include "../Headers/Cards.h"
#include "../Headers/includes.h"

using namespace std;

using enum Card::Figure;
using enum Card::Symbol;

using namespace std;

CardDeck Cards::generateDeck()
{
	CardDeck cards;
	for (auto const symbol : Card::symbols)
		for (auto const figure : Card::figures)
			cards.push_back(Card(symbol, figure));
	return cards;
}

void Cards::populateRandom(CardDeck& cards)
{
	for (int i = 0; i < 5; i++)
	{
		int x = random(0, cards.size());
		this->cards.push_back(cards[x]);
		cards.erase(cards.begin() + x);
	}

	// ciekawy sposób
	/*for (int& i : tab)
		i = random(0, cards.size());*/
}

size_t Cards::findByID(size_t ID)
{
	for (int i = 0; i < cards.size(); i++)
		if (cards[i].id == ID)
			return i;
	return -1;
}

size_t Cards::findByCardSymbols(Card::Symbol symbol, Card::Figure figure)
{
	for (int i = 0; i < cards.size(); i++)
		if (cards[i].symbol == symbol && cards[i].figure == figure)
			return i;
	return -1;
}