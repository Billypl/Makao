#include "../Headers/Turn.h"
#include "../Headers/Game.h"

void Turn::nextTurn()
{
	isCardPlaced = false;
	saidMakao = false;
	incrementCurrentPlayerNumber();
}

Turn::Turn()
	: currentPlayer(0), isCardPlaced(false), saidMakao(false)  {}

void Turn::incrementCurrentPlayerNumber()
{
	currentPlayer++;
	if (currentPlayer >= Game::PLAYERS_NUMBER)
		currentPlayer = 0;
}
