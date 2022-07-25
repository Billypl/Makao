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
	//return (this->id == other.id);
	return ((*this).figure == other.figure) && ((*this).symbol == other.symbol) && ((*this).id == other.id);
}

