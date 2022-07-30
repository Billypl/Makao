#include "../Headers/Turn.h"
#include "../Headers/Game.h"

void Turn::nextTurn()
{
	isCardPlaced = false;
	saidMakao = false;
	hasDrawedCard = false;
	incrementCurrentPlayerNumber();
	cls();
}

Turn::Turn()
	: currentPlayer(0), isCardPlaced(false), saidMakao(false), hasDrawedCard(false)  {}

void Turn::incrementCurrentPlayerNumber()
{
	currentPlayer++;
	if (currentPlayer >= Game::PLAYERS_NUMBER)
		currentPlayer = 0;
}
