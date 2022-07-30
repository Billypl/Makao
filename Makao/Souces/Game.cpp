#include "../Headers/Game.h"
#include <string>
using namespace std;

int Game::PLAYERS_NUMBER;

void Game::printTable()
{
    resetCardsState();
    grayOutCardsCannotBePlaced();
    printTableCard();
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

    printTableCard();
    for (int i = 0; i < PLAYERS_NUMBER; i++)
    {
        string indicator = "Player " + to_string(i + 1) + ": ";
        cout << indicator;
        players[i].printCards();
        cout << endl;
    }
}

void Game::printTableCard()
{
    const string BORDER_GAP = "\t\t";
    cout << "\n\n" << BORDER_GAP << cardsOnTable.back() << endl << BORDER_GAP;
    print(WHITE_B, "   \n\n\n\n");
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
    cardsOnTable.push_back(drawRandomStartingCard());
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

CardDeck Game::generateFullDeck()
{
    CardDeck cards;
    for (auto const symbol : Card::symbols)
        for (auto const figure : Card::figures)
            cards.push_back(Card(symbol, figure));
    return cards;
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

Card Game::drawRandomStartingCard()
{
    Card randomCard;
    while(true)
    {
        const int randomCardNumber = random::range(0, deck.size());
        randomCard = deck[randomCardNumber];
    	if(isSpecialCard(randomCard))
    		continue;
        deck.erase(next(deck.begin(), randomCardNumber));
        break;
    }
	return randomCard;
}

#include <ranges>

bool Game::isSpecialCard(Card randomCard)
{
    for (auto specialCard : CardParams::specialCards)
        if (randomCard.figure == specialCard)
            return true;
    return false;
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

    const Card pickedCard = players[turn.currentPlayer].cards.back();
    cardsOnTable.push_back(pickedCard);
	players[turn.currentPlayer].cards.pop_back();
}

void Game::grayOutCardsCannotBePlaced()
{
    for(auto& card : players[turn.currentPlayer].cards)
    {
        if(!canCardBePlaced(card))
    		card.canBePlaced = false;
    }
}

bool Game::canCardBePlaced(Card& card)
{
    if (cardsOnTable.back().figure == card.figure ||
        cardsOnTable.back().symbol == card.symbol ||
        cardsOnTable.back().figure == Q)
        return true;
    else 
        return false;
}

void Game::resetCardsState()
{
	for(auto& card : players[turn.currentPlayer].cards)
        card.canBePlaced = true;
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
        players[turn.currentPlayer].drawCards(deck, 1);

    else if (turn.saidMakao == false && players[turn.currentPlayer].cards.size() == 1)
    {
        players[turn.currentPlayer].drawCards(deck, 5);
        //print(RED_F, "You didn't say makao! Drawed 5 cards \n");
    }

	resetCardsState();
    turn.nextTurn();
}

