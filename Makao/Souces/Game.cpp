#include "../Headers/Game.h"
#include <string>
using namespace std;

int Game::PLAYERS_NUMBER;

void Game::printTable()
{
    for (int i = 0; i < PLAYERS_NUMBER; i++)
    {
        string indicator = "Player " + to_string(i + 1) + ": ";
        if (turn.currentPlayer == i)
        {
            print(MAGENTA_F, indicator);
            players[i].printCards();
            cout << endl;
            continue;
        }
        cout << indicator;
        players[i].printCoveredCards();
        cout << endl;
    }
}

void Game::printCheatTable()
{
    for (int i = 0; i < PLAYERS_NUMBER; i++)
    {
        string indicator = "Player " + to_string(i + 1) + ": ";
        cout << indicator;
        players[i].printCards();
        cout << endl;
    }
}

void Game::startGame()
{
	setupGame();
    startGameLoop();
}

void Game::setupGame()
{
    print(GREEN_F, "Welcome to makao game! \n");
	PLAYERS_NUMBER = waitForPlayersNumber();
    deck = Game::generateFullDeck();
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
        player.drawCards(deck, STARTING_CARDS_NUMBER);
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
        cls();
        string command = waitForUserCommand(); 
        chooseCommandFunc(command);

    }
}

string Game::waitForUserCommand()
{
    string command;
    while(true)
    {
        printTable();
        cout << "Choose from commands: | quit | play | cheat | makao | end | : ";
        cin >> command;
        for(auto commandName : commands)
        {
            if(command == commandName)
            {
                cls();
                return command;
            }
        }
        cls();
        print(RED_F, "Wrong command! Try again \n\n");
    }
}

void Game::chooseCommandFunc(string command)
{
    if (command == "quit") quit();
    if (command == "cheat")
    {
        cheat();
        return;
    }
    if (command == "makao")
    {
        makao();
        return;
    }
    // TODO: finish play command
    if (command == "play")
    {
        play();
        return;
    }
    // TODO: finish end command
    if (command == "end")
    {
        end();
        return;
    }

}

void Game::quit() { exit(0); }

void Game::play()
{
    turn.isCardPlaced = true;
	players[turn.currentPlayer].cards.pop_back();
}

void Game::cheat()
{
    printCheatTable();
    cout << "Type \"back\" to get back to normal view: ";
    string trash;
    cin >> trash;
}

void Game::makao()
{
    if (turn.isCardPlaced == false)
        return;
    turn.saidMakao = true;
}

void Game::end()
{
    if (turn.isCardPlaced == false)
    {
        players[turn.currentPlayer].drawCards(deck, 1);
    	turn.nextTurn();
        return;
    }
    if (turn.saidMakao == false && players[turn.currentPlayer].cards.size() == 1)
    {
        players[turn.currentPlayer].drawCards(deck, 5);
        turn.nextTurn();
        print(RED_F, "You didn't say makao! Drawed 5 cards \n");
        return;
    }
    turn.nextTurn();
}

