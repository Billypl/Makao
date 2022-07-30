#pragma once
#include <array>
#include <string>
#include "options.h"

// HACK: Symbole kart
// czasami znaki specjalne nie wyświetlają się prawidłowo
// zakomentować odpowiednią opcję w pliku "options.h"

#ifdef SYMBOLS 

#define CLUBS		"♣"
#define DIAMONDS	"♦"
#define HEARTS		"♥"
#define SPADES		"♠"

#else

#define CLUBS		"_c"
#define DIAMONDS	"_d"
#define HEARTS		"_h"
#define SPADES		"_s"

#endif


class CardParams
{
public:

	enum class Symbol
	{
		clubs,		//(♣)
		diamonds,	//(♦)
		hearts,		//(♥)
		spades		//(♠)
	};
	using enum Symbol;
	static inline std::array<Symbol, 4> symbols = { clubs, diamonds, hearts, spades };

	enum class Figure
	{
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
		_10,
		J,
		Q,
		K,
		A
	};
	using enum Figure;
	static inline std::array<Figure, 13> figures = { _2,_3,_4,_5,_6,_7,_8,_9,_10,J,Q,K,A };

	enum class Color
	{
		black,
		red
	};

	static inline std::array<Figure, 7> specialCards = { _2,_3,_4,J,Q,K,A };

};

class Card : public CardParams
{

public:

	bool operator== (const Card& other) const;
	friend std::ostream& operator<< (std::ostream& cout, Figure figure);
	friend std::ostream& operator<< (std::ostream& cout, Symbol symbol);
	friend std::ostream& operator<< (std::ostream& cout, const Card& card);

	size_t id;
	Symbol symbol;
	Figure figure;
	Color color;
	bool canBePlaced;

	Card();
	Card(const Card& card); // konstruktor kopiujący
	Card(Symbol symbol, Figure figure); 

private:
	size_t generateId();
	Color determineColor(Symbol symbol);

};

