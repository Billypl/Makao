#include "../Headers/includes.h"
#include "../Headers/Card.h"
#include <iostream>
#include "../Headers/Turn.h"

using namespace std;

Color Card::determineColor(Symbol symbol)
{
	if (symbol == clubs || symbol == spades)
		return Color::black;
	else
		return Color::red;
}

size_t Card::generateId()
{
	size_t id = (int)symbol * 100 + (int)figure;
	return id;
}

Card::Card() {}

Card::Card(Symbol symbol, Figure figure)
	: symbol(symbol), figure(figure), canBePlaced(true)
{
	color = determineColor(symbol);
	id = generateId();
}


Card::Card(const Card& card)
	: Card(card.symbol, card.figure) {}

bool Card::operator== (const Card& other) const
{
	return (this->id == other.id);
}

std::ostream& operator<<(std::ostream& cout, Figure figure)
{
	using enum Card::Figure;
	switch(figure)
	{
		case _2:
			cout << "2";
			break;
		case _3:
			cout << "3";
			break;
		case _4:
			cout << "4";
			break;
		case _5:
			cout << "5";
			break;
		case _6:
			cout << "6";
			break;
		case _7:
			cout << "7";
			break;
		case _8:
			cout << "8";
			break;
		case _9:
			cout << "9";
			break;
		case _10:
			cout << "10";
			break;
		case J:
			cout << "J";
			break;
		case Q:
			cout << "Q";
			break;
		case K:
			cout << "K";
			break;
		case A:
			cout << "A";
			break;
	}
	return cout;
}

std::ostream& operator<<(std::ostream& cout, Symbol symbol)
{
	using enum Card::Symbol;
	switch (symbol)
	{
	case spades:
		cout << SPADES;
		break;
	case clubs:
		cout << CLUBS;
		break;
	case diamonds:
		cout << DIAMONDS;
		break;
	case hearts:
		cout << HEARTS;
		break;
	}
	return cout;
}

std::ostream& operator<<(std::ostream& cout, const Card& card)
{
	string COLOR;
	if (card.canBePlaced)
		COLOR = WHITE_B;
	else
		COLOR = GRAY_B;

	if (card.color == Color::black)
		COLOR += BLACK_F;
	else
		COLOR += RED_F;

	if(card.figure == _10)
		cout << COLOR << card.figure << card.symbol << DEFAULT_B DEFAULT_F;
	else
		cout << COLOR << " " << card.figure << card.symbol << DEFAULT_B DEFAULT_F;

	return cout;
}


bool isNeedToDrawCard(const Turn& turn);
bool canAnotherSpecialCardBePlaced(const Turn& turn, const Card& card);
bool canPlayerDefend(CardDeck& cardsOnTable, const Turn& turn, const Card& card);
bool Card::canCardBePlaced(CardDeck& cardsOnTable, const Turn& turn)
{
	if(isNeedToDrawCard(turn))
	{
		if (canAnotherSpecialCardBePlaced(turn, *this))
			return true;
		if (canPlayerDefend(cardsOnTable, turn, *this))
			return true;
		return false;
	}
	if (turn.isCardPlaced)
		return isMatchingCardPlacedInTheSameTurn(turn);
	return isMatchingCardOnTheTable(cardsOnTable, turn);

}

bool isNeedToDrawCard(const Turn& turn)
{
	return turn.drawAmount != 0;
}

bool canAnotherSpecialCardBePlaced(const Turn& turn, const Card& card)
{
	return turn.isCardPlaced && turn.lastPlacedCard.figure == card.figure;
}

bool canPlayerDefend(CardDeck& cardsOnTable, const Turn& turn, Card& card)
{
	return !turn.isCardPlaced && (
		(card.is_2or_3(cardsOnTable) && (card.isCardCounterFor_2(cardsOnTable) || card.isCardCounterFor_3(cardsOnTable))) ||
		(card.isCardCounterFor_K(cardsOnTable))
		);
}

bool Card::isCardCounterFor_2(CardDeck& cardsOnTable)
{
	return cardsOnTable.back().figure == _2 && figure == _2 ||
		cardsOnTable.back().figure == _2 && figure == _3 && symbol == cardsOnTable.back().symbol;
}

bool Card::isCardCounterFor_3(CardDeck& cardsOnTable)
{
	return cardsOnTable.back().figure == _3 && figure == _3 ||
		cardsOnTable.back().figure == _3 && figure == _2 && symbol == cardsOnTable.back().symbol;
}

bool Card::isCardCounterFor_K(CardDeck& cardsOnTable)
{
	return cardsOnTable.back().figure == K && figure == K;
}

bool Card::is_2or_3(CardDeck& cardsOnTable)
{
	return cardsOnTable.back().figure == _2 || cardsOnTable.back().figure == _3;
}

bool Card::isSpecial_K(CardDeck& cardsOnTable)
{
	return cardsOnTable.back().figure == K && cardsOnTable.back().symbol == spades ||
		cardsOnTable.back().figure == K && cardsOnTable.back().symbol == hearts;
}

bool Card::isMatchingCardPlacedInTheSameTurn(const Turn& turn)
{
	return turn.lastPlacedCard.figure == figure;
}

bool Card::isMatchingCardOnTheTable(CardDeck& cardsOnTable, const Turn& turn)
{
	return isStandard(cardsOnTable, turn);
}

bool Card::isStandard(CardDeck& cardsOnTable, const Turn& turn)
{
	return (figure == Q ||
		turn.lastPlacedCard.figure == Q ||
		turn.lastPlacedCard.figure == figure ||
		turn.lastPlacedCard.symbol == symbol);
}