//
//  myConstants.h
//  Blackjack
//
//  Created by Shafi Bashar on 7/6/14.
//  Copyright (c) 2014 Shafi Bashar. All rights reserved.
//

#ifndef Blackjack_myConstants_h
#define Blackjack_myConstants_h

enum Outcome {PUSH, DEALER_WIN, PLAYER_WIN, NONE, DEALER_BUST, PLAYER_BUST, PLAYER_BJ, DEALER_BJ};
enum PlayerAction {HIT, STAND, DOUBLE, SPLIT, NO};
const int NUM_CARD_DECK = 52;
const int NUM_CARD_SUIT = 13;
const std::string SUITS[] = {"\u2663","\u2666","\u2665", "\u2660"}; // symbols for clubs, diamonds, hearts and spades
const std::string SUITS_text[] = {"Clubs","Diamonds","Hearts","Spades"};
const std::string RANK[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
const int BJ = 21;
const int TwentyOne = 21;
const int VALUE[] =  {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11}; // blackjack value of each rank


#endif
