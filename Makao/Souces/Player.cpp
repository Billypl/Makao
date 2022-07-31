#include "../Headers/Player.h"
#include "../Headers/Game.h"
#include "../Headers/includes.h"
using namespace std;

Player::Player()
	: isBot(false) {}

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

size_t Player::findCard(Card card)
{
	return findCardBySymbol(card.symbol, card.figure);
}

void Player::printCards()
{
	printUpperOfCards();
	cout << PLAYER_CARDS_INDICATOR_GAP;
	printBottomOfCards();
}

void Player::printCoveredCards()
{
	printBottomOfCards();
	cout << PLAYER_CARDS_INDICATOR_GAP;
	printBottomOfCards();
}

void Player::printUpperOfCards()
{
	for (const auto& card : cards)
		cout << card << " ";
	cout << endl;
}

void Player::printBottomOfCards()
{
	for (const auto& card : cards)
	{
		if(card.canBePlaced)
			print(WHITE_B, "   ");
		else
			print(GRAY_B, "   ");
		cout << " ";
	}
	cout << endl;
}

bool Player::didWin()
{
	return cards.empty();
}