#include "../Headers/includes.h"
#include <iostream>

class Turn;
using namespace std;

Color Card::determineColor(Symbol symbol)
{
	if (symbol == Symbol::clubs || symbol == Symbol::spades)
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

bool Card::canCardBePlaced(CardDeck& cardsOnTable)
{
	if (figure == Q || 
		cardsOnTable.back().figure == Q ||
		cardsOnTable.back().figure == figure ||
		cardsOnTable.back().symbol == symbol)
		return true;
	else
		return false;
}