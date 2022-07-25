#include <iostream>
#include "Headers/Cards.h"

using namespace std;


int main()
{
    srand(time(NULL));
    Cards table;
    table.cards = Cards::generateDeck();
    Cards c1;
    c1.populateRandom(table.cards);


    cout << "Works?";
}
