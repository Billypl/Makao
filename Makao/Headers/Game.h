// ReSharper disable CppVariableCanBeMadeConstexpr
#pragma once
#include <iostream>
#include "Player.h"
#include "Turn.h"
#include <string>
#include <array>

const int STARTING_CARDS_NUMBER = 5;
const std::string PLAYER_CARDS_INDICATOR_GAP = "          ";

class Game
{
	std::vector<Player> players;
	CardDeck deck;
	CardDeck cardsOnTable;
	Turn turn;
	std::array<std::string, 5> commands = { "quit", "play", "cheat", "makao", "end" };

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

	void quit();
	void cheat();
	void play();
	void makao();

	void printTable();
	void printCheatTable();
	
};

