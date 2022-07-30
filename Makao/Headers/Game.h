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

	void printTable();
	void printCheatTable();

	void quit();
	void cheat();
	void play();

	//std::string waitForCardToChoose();
	void makao();
	void end();

private:

	void printTableCard();

	void setupGame();
	int waitForPlayersNumber();
	static CardDeck generateFullDeck();
	std::vector<Player> createPlayers();
	Card drawRandomStartingCard();
	bool isSpecialCard(Card randomCard);
	void startGameLoop();

	std::string waitForUserCommand();
	void chooseCommandFunc(std::string command);
	
	void grayOutCardsCannotBePlaced();
	bool canCardBePlaced(Card& card);
	void resetCardsState();
	
};

