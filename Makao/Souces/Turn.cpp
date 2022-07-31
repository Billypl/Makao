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
	: currentPlayer(0), isCardPlaced(false), saidMakao(false), hasDrawedCard(false), botPickedOption(0)  {}

void Turn::incrementCurrentPlayerNumber()
{
	currentPlayer++;
	if (currentPlayer >= Game::PLAYERS_NUMBER)
		currentPlayer = 0;
}

int Turn::incrementBotPickedNumber()
{
	int pickedOption = botPickedOption;
	botPickedOption++;
	if (botPickedOption > 2)
		botPickedOption = 0;
	return pickedOption;
}