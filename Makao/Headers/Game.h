// ReSharper disable CppVariableCanBeMadeConstexpr
#pragma once
#include <iostream>
#include "Player.h"
#include "Turn.h"
#include  <string>

const int STARTING_CARDS_NUMBER = 5;

class Game
{
	std::vector<Player> players;
	CardDeck table;
	Turn turn;

public:

	static int PLAYERS_NUMBER;
	void startGame();

private:

	void setupGame();
	int waitForPlayersNumber();
	std::vector<Player> createPlayers();
	static CardDeck generateFullDeck();
	void startGameLoop();
	std::string waitForUserCommand();
	void chooseCommandFunc(std::string command);

};

