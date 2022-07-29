#pragma once
class Turn
{
public:

	int currentPlayer;
	bool isCardPlaced;
	bool saidMakao;

	void nextTurn();
	Turn();
private:

	void incrementCurrentPlayerNumber();
};

