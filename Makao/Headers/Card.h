#pragma once
#include <array>
#include <string>

// HACK: Symbole kart
// czasami znaki specjalne nie wyświetlają się prawidłowo
// zakomentować poniższą linijkę jeśli nie działa
#define SYMBOLS

#ifdef SYMBOLS 

#define CLUBS		"♣"
#define DIAMONDS	"♦"
#define HEARTS		"♥"
#define SPADES		"♠"

#else

#define CLUBS		"clubs"
#define DIAMONDS	"diamonds"
#define HEARTS		"hearts"
#define SPADES		"spades"

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
};

class Card : public CardParams
{

public:

	bool operator== (const Card& other) const;
	//Card& operator= (const Card& other);
	friend std::ostream& operator<< (std::ostream& cout, Figure figure);
	friend std::ostream& operator<< (std::ostream& cout, Symbol symbol);
	friend std::ostream& operator<< (std::ostream& cout, Card card);


	size_t id;
	Symbol symbol;
	Figure figure;
	Color color;

	Card();
	Card(const Card& card);
	Card(Symbol symbol, Figure figure);

private:
	size_t generateId();
	Color determineColor(Symbol symbol);

};

