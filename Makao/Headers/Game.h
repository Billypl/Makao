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
	std::array<std::string, 6> commands = { "play", "makao", "end", "draw", "cheat", "quit" };

public:

	static int PLAYERS_NUMBER;
	static int BOTS_NUMBER;

	void startGame();

	void printTable();
	void printCheatTable();

	Player& getCurrentPlayer();

	void quit();
	void cheat();
	int play();

	void makao();
	void end();
	void draw();
	int getPlayersLeftCount();

private:

	void printTableCard();

	void setupGame();
	int waitForPlayersNumber();
	int waitForBotsNumber();
	static CardDeck generateFullDeck();
	std::vector<Player> createPlayers();
	Card drawRandomStartingCard();
	bool isSpecialCard(Card randomCard);

	void startGameLoop();

	std::string waitForUserCommand();
	void chooseCommandFunc(std::string command);

	void grayOutCardsCannotBePlaced();
	void resetCardsState();

	int waitForCardNumber();
	bool canANYcardBePlaced();

	void shuffleDeck();

	void drawCardIfHavent();
	void drawFiveCardsIfNotMakao();

	void changeDrawAmount();

	void waitForPlayerToChooseSymbol();

};

