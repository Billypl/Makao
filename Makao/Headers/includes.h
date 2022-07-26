#pragma once
// wszystkie ważne deklaracje, które mogą być potencjalnie użyte
// pomiędzy plikami są tutaj
#include <iostream>
#include <cstdlib>

#include "Card.h"
#include "console.h"

typedef Card::Color Color;
typedef Card::Symbol Symbol;
typedef Card::Figure Figure;


// definicja w Card.cpp
std::ostream& operator<< (std::ostream& cout, Figure figure);
std::ostream& operator<< (std::ostream& cout, Symbol symbol);
std::ostream& operator<< (std::ostream& cout, Card card);

class random
{
public:
	random() { srand(time(NULL)); }
	static int range(int rangeStart, int rangeEnd) { return (rand() % (rangeEnd + 1 - rangeStart) + rangeStart); }
};

