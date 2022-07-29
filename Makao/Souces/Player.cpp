#include "../Headers/Player.h"
#include "../Headers/includes.h"


void Player::drawCards(CardDeck& deck, int cardCount)
{
	for (int i = 0; i < cardCount; i++)
	{
		int x = random::range(0, deck.size() - 1);
		this->cards.push_back(deck[x]);
		deck.erase(deck.begin() + x);
	}
}

size_t Player::findCardByID(size_t ID)
{
	for (int i = 0; i < cards.size(); i++)
		if (cards[i].id == ID)
			return i;
	return -1;
}

size_t Player::findCardBySymbol(Card::Symbol symbol, Card::Figure figure)
{
	for (int i = 0; i < cards.size(); i++)
		if (cards[i].symbol == symbol && cards[i].figure == figure)
			return i;
	return -1;
}