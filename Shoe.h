//
//  Shoe.h
//  Blackjack
//
//  Created by Shafi Bashar on 7/6/14.
//  Copyright (c) 2014 Shafi Bashar. All rights reserved.
//
#include <random>
#include <algorithm>

#ifndef Blackjack_Shoe_h
#define Blackjack_Shoe_h

class Shoe
{
    int NumDeck;
    stack<int> ShoeCard;
    unsigned int Seed;
public:
    Shoe(int n, unsigned int s):NumDeck(n), Seed(s){}
    void CreateShoe(); // put shuffled card in the shoe
    int pullCard(); // return a card from the shoe
    
};

void Shoe::CreateShoe()
{
    vector<int> tempShoe;
    for (int i=0;i<NUM_CARD_DECK*NumDeck;i++) tempShoe.push_back(i);
    shuffle(tempShoe.begin(),tempShoe.end(),std::default_random_engine(Seed));
    for (int i=0;i<NUM_CARD_DECK*NumDeck;i++) ShoeCard.push(tempShoe[i]);
}

int Shoe::pullCard()
{
    int CardId = -1;
    if (!ShoeCard.empty())
        CardId = ShoeCard.top();
    ShoeCard.pop();
    return CardId;
}



#endif
