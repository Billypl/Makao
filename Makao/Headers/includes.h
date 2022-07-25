#pragma once

#include "Card.h"
typedef Card::Color Color;
typedef Card::Symbol Symbol;
typedef Card::Figure Figure;

inline int random(int rangeStart, int rangeEnd) { return (rand() % (rangeEnd + 1)) + rangeStart; }