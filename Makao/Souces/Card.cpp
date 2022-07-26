#include "../Headers/includes.h"
#include <iostream>

using namespace std;

Color Card::determineColor(Symbol symbol)
{
	if (symbol == Symbol::clubs || symbol == Symbol::spades)
		return Color::black;
	else
		return Color::red;
}

Card::Card(Symbol symbol, Figure figure)
	: symbol(symbol), figure(figure) 
{
	color = determineColor(symbol);
	id = generateId();
}

size_t Card::generateId()
{
	size_t id = (int)symbol * 100 + (int)figure;
	return id;
}


Card::Card() {}

Card::Card(const Card& card)
	: Card(card.symbol, card.figure) {}

bool Card::operator== (const Card& other) const
{
	return (this->id == other.id);
}

//Card& Card::operator=(const Card& other)
//	: Card(this.)
//{
//}



std::ostream& operator<<(std::ostream& cout, Figure figure)
{
	using enum Card::Figure;
	switch(figure)
	{
		case _2:
			cout << "_2";
			break;
		case _3:
			cout << "_3";
			break;
		case _4:
			cout << "_4";
			break;
		case _5:
			cout << "_5";
			break;
		case _6:
			cout << "_6";
			break;
		case _7:
			cout << "_7";
			break;
		case _8:
			cout << "_8";
			break;
		case _9:
			cout << "_9";
			break;
		case _10:
			cout << "_10";
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

std::ostream& operator<<(std::ostream& cout, Card card)
{
	string COLOR;
	if (card.color == Color::black)
		COLOR = WHITE_B BLACK_F;
	else
		COLOR = WHITE_B RED_F;

	cout << COLOR << card.figure  << card.symbol << DEFAULT_B DEFAULT_F;
	return cout;
}

