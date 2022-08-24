#include "../Headers/Game.h"
#include "../Headers/Card.h"
#include "../Headers/includes.h"
#include <string>
using namespace std;

int Game::PLAYERS_NUMBER;
int Game::BOTS_NUMBER;

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
    print(WHITE_B, "  " + (string)SYMBOL_LENGTH);
    cout << "\n\n\n\n";
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

void printWelcomeScreen();
void Game::setupGame()
{
    printWelcomeScreen();
    PLAYERS_NUMBER = waitForPlayersNumber();
    BOTS_NUMBER = waitForBotsNumber();
    deck = Game::generateFullDeck();
    cardsOnTable.push_back(drawRandomStartingCard());
    turn.lastPlacedCard = cardsOnTable.back();
    players = createPlayers();
}

void printWelcomeScreen()
{
    print(GREEN_F, "Welcome to makao game! \n\n");
    cout << YELLOW_F;
    cout << "There are 6 commands you need to know: \n";
    cout << "quit - exits the program \n";
    cout << "play - let's you (if there are any available) choose a card\n";
    cout << "makao - can be used when user have 1 card\n";
    cout << "cheat - shows all cards\n";
    cout << "draw - lets you draw 1 card\n";
    cout << "end - ends your turn and draws card/cards if you didn't\n\n";
    cout << DEFAULT_F;
}

int Game::waitForPlayersNumber()
{
    while (true)
    {
	    cout << "Please insert number of players: ";
        int playersNumber = getIntFromUser();
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

int Game::waitForBotsNumber()
{
    while (true)
    {
        cout << "Please insert number of real players (played by user): ";
        int realPlayers = getIntFromUser();
        if (realPlayers < 1)
        {
            cout << "You need more players to play! Bots playing with themselves are boring! \n";
            continue;
        }
        if (realPlayers > 4)
        {
            cout << "Too much players! \n";
            continue;
        }
        return PLAYERS_NUMBER - realPlayers;
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
    // create method creates 5 more users
    vector<Player> players;
    int i = 0;
    for(i; i < PLAYERS_NUMBER - BOTS_NUMBER; i++)
    {
        Player player;
        player.drawCards(deck, STARTING_CARDS_NUMBER);
	    players.push_back(player);
    }
    for (i; i < PLAYERS_NUMBER; i++)
    {
        Player player;
        player.isBot = true;
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
        // needed just for game over screen
        cls();
        printTable();

        if (getPlayersLeftCount() == 1)
        {
            print(GREEN_F, "\n\n\n GAME OVER \n\n\n");
            quit();
        }
        if (getCurrentPlayer().didWin())
            turn.nextTurn();
        cls();


        string command = waitForUserCommand(); 
        chooseCommandFunc(command);
    }
}

int Game::getPlayersLeftCount()
{
    int playersInGame = 0;
	for (const auto& player : players)
        if (player.cards.empty() == false)
            playersInGame++;
    return playersInGame;
}


string Game::waitForUserCommand()
{
    string command;
    while(true)
    {
        printTable();
        cout << "Choose from commands: | quit | play | cheat | makao | end | draw | : ";

        // bot block
        if (getCurrentPlayer().isBot)
            return commands[turn.incrementBotPickedNumber()];

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
        do 
        {
            if (play() == -1)
                return;
        } while(getCurrentPlayer().isBot);

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

int Game::play()
{
    const int cardNumberToPutOnTable = waitForCardNumber();
    if (cardNumberToPutOnTable == -1)
        return -1;
    
    const Card pickedCard = getCurrentPlayer().cards[cardNumberToPutOnTable-1];

    // special cards _2 and _3
    if(pickedCard.figure == _2)
        turn.drawAmount += 2;
    if (pickedCard.figure == _3)
        turn.drawAmount += 3;
    if(pickedCard.figure == K && (pickedCard.symbol == spades || pickedCard.symbol == hearts))
        turn.drawAmount += 5;
    if (pickedCard.figure == K && (pickedCard.symbol == diamonds || pickedCard.symbol == clubs))
        turn.drawAmount = 0;

    // for requirements of special card AS
    turn.lastPlacedCard = pickedCard;

    cardsOnTable.push_back(pickedCard);
	const int indexOfPickedCardOnPlayerHand = getCurrentPlayer().findCard(pickedCard);
    getCurrentPlayer().cards.erase(next(getCurrentPlayer().cards.begin(), indexOfPickedCardOnPlayerHand));
	turn.isCardPlaced = true;

    return 0;
}

void Game::waitForPlayerToChooseSymbol()
{
    cls();
    printTable();

    array<Card, 4> As =
    {
        Card(clubs, A),
        Card(spades, A),
        Card(hearts, A),
        Card(diamonds, A)
    };

    while (true)
    {
        cout << "Choose number of the of the aviable symbols ( ";
        print(WHITE_B BLACK_F, CLUBS);
        cout << " ";
        print(WHITE_B BLACK_F, SPADES);
        cout << " ";
        print(WHITE_B RED_F, HEARTS);
        cout << " ";
        print(WHITE_B RED_F, DIAMONDS);
    	cout << " ): ";

        // bot block
        if (getCurrentPlayer().isBot)
        {
            turn.lastPlacedCard = As[random::range(0, 3)];
        	return;
        }

        int symbol = getIntFromUser();
        if (As.size() < symbol)
        {
            print(RED_F, "There are only 4 aviable symbols\n");
            continue;
        }
        if (1 > symbol)
        {
            print(RED_F, "Symbol indexes stars from 1\n");
            continue;
        }
        turn.lastPlacedCard = As[symbol - 1];
        return;
    }
}

void Game::changeDrawAmount()
{
    if (cardsOnTable.back().figure == _2)
        turn.drawAmount += 2;
    if (cardsOnTable.back().figure == _2)
        turn.drawAmount += 3;
}



int Game::waitForCardNumber()
{
    printTable();
    if (canANYcardBePlaced() == false)
        return -1;
   
    int botCounter = 1;
    while(true)
    {
        cout << "Choose number of the card you want to place: ";
        int cardNumber;

        // bot block
        if (getCurrentPlayer().isBot)
            cardNumber = botCounter++;
        else
            cardNumber = getIntFromUser();

    	if (getCurrentPlayer().cards.size() < cardNumber)
        {
            print(RED_F, "You don't have so many cards to! Choose number of the card you have\n");
            continue;
        }
        if (1 > cardNumber)
        {
            print(RED_F, "Card indexes stars from 1\n");
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
    turn.isMakaoSaid = true;
}

void Game::draw()
{
    if(turn.isCardPlaced == false && turn.isCardDrawn == false)
    {
        // special card _2 or _3
        if(turn.drawAmount != 0)
			turn.drawAmount--;

        if (deck.empty())
            shuffleDeck();
        turn.isCardDrawn = true;
		getCurrentPlayer().drawCards(deck, 1);
    }
}

// finish play command //canPlaceCard
void Game::end()
{
    if (turn.lastPlacedCard.figure == A && turn.isCardPlaced)
        waitForPlayerToChooseSymbol();

    // special card _2 or _3
    if (!turn.isCardPlaced && cardsOnTable.back().is_2or_3(cardsOnTable) && turn.drawAmount != 0)
    {
        getCurrentPlayer().drawCards(deck, turn.drawAmount);
        turn.drawAmount = 0;
        turn.isCardDrawn = true;
    }
    // special card K
    if (!turn.isCardPlaced && cardsOnTable.back().isSpecial_K(cardsOnTable) && turn.drawAmount!=0)
    {
        getCurrentPlayer().drawCards(deck, turn.drawAmount);
        turn.drawAmount = 0;
        turn.isCardDrawn = true;
    }
    if (turn.drawAmount != 0 && turn.isCardDrawn)
		turn.drawAmount++;

	resetCardsState();
    drawCardIfHavent();
    drawFiveCardsIfNotMakao();
    if (turn.drawAmount !=0 && !turn.isCardDrawn && turn.lastPlacedCard.symbol == spades && turn.lastPlacedCard.figure == K)
        turn.decrementCurrentPlayerNumber();
    turn.nextTurn();
}

void Game::drawCardIfHavent()
{
    if (turn.isCardPlaced == false && turn.isCardDrawn == false)
    {
        if (deck.empty())
            shuffleDeck();
        getCurrentPlayer().drawCards(deck, 1);
    }
}

void Game::drawFiveCardsIfNotMakao()
{
    if (turn.isMakaoSaid == false && getCurrentPlayer().cards.size() == 1 && turn.isCardPlaced)
    {
        if (deck.size() < 5)
            shuffleDeck();
        getCurrentPlayer().drawCards(deck, 5);
    }
}

void Game::shuffleDeck()
{
    deck.insert(deck.end(), cardsOnTable.begin(), cardsOnTable.end() - 1);
	cardsOnTable.erase(cardsOnTable.begin(), cardsOnTable.end() - 1);
}
