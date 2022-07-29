#include "../Headers/Game.h"
using namespace std;

int Game::PLAYERS_NUMBER;

void Game::startGame()
{
	setupGame();
    startGameLoop();
}

void Game::setupGame()
{
	cout << "Welcome to makao game! \n";
	/*DEBUG*/ PLAYERS_NUMBER = 2;
	//PLAYERS_NUMBER = waitForPlayersNumber();
    table = Game::generateFullDeck();
    players = createPlayers();
}

int Game::waitForPlayersNumber()
{
    int playersNumber = 2;
    while (true)
    {
	    cout << "Please insert number of players: ";
        cin >> playersNumber;
        if (playersNumber < 2)
        {
            cout << "You need more players to play! \n";
            continue;
        }
        if (playersNumber > 4)
        {
            cout << "Too much players! \n";
            continue;
        }
        return playersNumber;
    }
}

vector<Player> Game::createPlayers()
{
    vector<Player> players;
    for(int i = 0; i < PLAYERS_NUMBER; i++)
    {
        Player player;
        player.drawCards(table, STARTING_CARDS_NUMBER);
	    players.push_back(player);
    }
    return players;
}

CardDeck Game::generateFullDeck()
{
    CardDeck cards;
    for (auto const symbol : Card::symbols)
        for (auto const figure : Card::figures)
            cards.push_back(Card(symbol, figure));
    return cards;
}

void Game::startGameLoop()
{
    while(true)
    {
        string command = waitForUserCommand(); 

        turn.nextTurn();
    }
}

string Game::waitForUserCommand()
{
    string command;
    while(true)
    {
        cout << "Choose from commands: quit | play | cheat | makao: ";
        cin >> command;
        if (command == "quit" || command == "play" || command == "cheat" || command == "makao")
            return command;
        cout << "Wrong command! Try again \n";
    }
}

