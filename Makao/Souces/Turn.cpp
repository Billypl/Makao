#include "../Headers/Turn.h"
#include "../Headers/Game.h"

void Turn::nextTurn()
{
	isCardPlaced = false;
	isMakaoSaid = false;
	isCardDrawn = false;
	incrementCurrentPlayerNumber();
	cls();
}

Turn::Turn()
	: currentPlayer(0), isCardPlaced(false), isMakaoSaid(false), isCardDrawn(false), botPickedOption(0)  {}

void Turn::incrementCurrentPlayerNumber()
{
	currentPlayer++;
	if (currentPlayer >= Game::PLAYERS_NUMBER)
		currentPlayer = 0;
}

void Turn::decrementCurrentPlayerNumber()
{
	currentPlayer -= 2;
	if (currentPlayer < 0)
		currentPlayer = Game::PLAYERS_NUMBER + currentPlayer;
}

int Turn::incrementBotPickedNumber()
{
	int pickedOption = botPickedOption;
	botPickedOption++;
	if (botPickedOption > 2)
		botPickedOption = 0;
	return pickedOption;
}