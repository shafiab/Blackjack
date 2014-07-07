//
//  main.cpp
//  Blackjack
//
//  Created by Shafi Bashar on 7/5/14.
//  Copyright (c) 2014 Shafi Bashar. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <chrono>
#include "myConstants.h"
#include "Account.h"
#include "Player.h"
#include "Shoe.h"
#include "Text.h"
#include "Board.h"
using namespace std;

int main(int argc, const char * argv[])
{
    // initial set up (this can be changed depending on the need)
    int NumPlayer = 1;  // number of players
    int NumDeck = 4;    // number of deck of cards in the shoe
    bool isRandomSeed = true; // true: random seed, false: fixed seed
    unsigned int Seed = 100;      // Seed for fixed seed case
    int initialAccountValue = 100; //account value for each player
    bool useTextSymbol = false; // whether to use Unicode symbol or text for suits
    
    // initialize text graphics and accounting
    Text myText(NumPlayer, initialAccountValue, useTextSymbol);
    myText.printWelcomeMessage(); // print welcome message
    myText.accountSetup(); //setup account
    myText.printAccount();

    // set seed
    if (isRandomSeed) // if random seed then create Seed
        Seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
    
    // initialize board setup and play related
    Board myBoard(NumPlayer, NumDeck, Seed);
    myBoard.createBoard();
    
    vector<Outcome> result; // result vector for each play
    while (myText.playerBetInput())
    {
        myBoard.initializeBoard(myText); // at each play initialize player and board
        myBoard.runGame(myText, result); // run game
        result.clear(); // clear result for next play
        myText.printAccount(); // print account status
    }
    
    return 0;
}

