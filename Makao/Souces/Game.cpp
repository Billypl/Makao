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

Player& Game::getCurrentPlayer()
{
    return players[turn.currentPlayer];
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
        const int randomCardNumber = random::range(0, deck.size() - 1);
        randomCard = deck[randomCardNumber];
    	if(isSpecialCard(randomCard))
    		continue;
        deck.erase(next(deck.begin(), randomCardNumber));
        break;
    }
	return randomCard;
}

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
        if (getCurrentPlayer().didWin())
            turn.nextTurn();
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
        cout << "Choose from commands: | quit | play | cheat | makao | end | draw | : ";
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
    if(command == "draw")
    {
        draw();
        return;
    }

}


void Game::quit() { exit(0); }

void Game::play()
{
    const int cardNumberToPutOnTable = waitForCardNumber();
    if (cardNumberToPutOnTable == -1)
        return;
    
    const Card pickedCard = getCurrentPlayer().cards[cardNumberToPutOnTable-1];
    cardsOnTable.push_back(pickedCard);
	const int indexOfPickedCardOnPlayerHand = getCurrentPlayer().findCard(pickedCard);
    getCurrentPlayer().cards.erase(next(getCurrentPlayer().cards.begin(), indexOfPickedCardOnPlayerHand));
	turn.isCardPlaced = true;
}

int Game::waitForCardNumber()
{
    printTable();
    if (canANYcardBePlaced() == false)
        return -1;
    while(true)
    {
        cout << "Choose number of the card you want to place: ";
        int cardNumber;
        cin >> cardNumber;
        if (getCurrentPlayer().cards.size() < cardNumber)
        {
            print(RED_F, "You don't have so many cards to! Choose number of the card you have\n");
            continue;
        }

        if (getCurrentPlayer().cards[cardNumber - 1].canCardBePlaced(cardsOnTable, turn) == true)
            return cardNumber;
        else
            print(RED_F, "This card can't be placed! Choose another\n");
    }
}

bool Game::canANYcardBePlaced()
{
	for (const auto& card : getCurrentPlayer().cards)
	{
	    if (!card.canBePlaced)
	        continue;
	    return true;
	}
	return false;
}

void Game::grayOutCardsCannotBePlaced()
{
    for(auto& card : getCurrentPlayer().cards)
    {
        if(!card.canCardBePlaced(cardsOnTable, turn))
    		card.canBePlaced = false;
    }
}

void Game::resetCardsState()
{
	for(auto& card : getCurrentPlayer().cards)
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

void Game::draw()
{
    if(turn.isCardPlaced == false && turn.hasDrawedCard == false)
    {
        turn.hasDrawedCard = true;
		getCurrentPlayer().drawCards(deck, 1);
    }
}

// finish play command //canPlaceCard
void Game::end()
{
	resetCardsState();
    drawCardIfHavent();
    drawFiveCardsIfNotMakao();
    turn.nextTurn();
}

void Game::drawCardIfHavent()
{
    if (turn.isCardPlaced == false && turn.hasDrawedCard == false)
    {
        if (deck.empty())
            shuffleDeck();
        getCurrentPlayer().drawCards(deck, 1);
    }
}

void Game::drawFiveCardsIfNotMakao()
{
    if (turn.saidMakao == false && getCurrentPlayer().cards.size() == 1 && turn.isCardPlaced)
    {
        if (deck.size() < 5)
            shuffleDeck();
        getCurrentPlayer().drawCards(deck, 5);
        //print(RED_F, "You didn't say makao! Drawed 5 cards \n");
    }
}

void Game::shuffleDeck()
{
    deck.insert(deck.end(), cardsOnTable.begin(), cardsOnTable.end() - 1);
	cardsOnTable.erase(cardsOnTable.begin(), cardsOnTable.end() - 1);
}


