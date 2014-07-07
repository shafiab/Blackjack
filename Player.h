//
//  Player.h
//  Blackjack
//
//  Created by Shafi Bashar on 7/6/14.
//  Copyright (c) 2014 Shafi Bashar. All rights reserved.
//

#ifndef Blackjack_Player_h
#define Blackjack_Player_h

using namespace std;
class Player
{
    int Id;
    bool isSplit;
    string SplitId;
    vector<int> Card;
    int playerBet;
    friend class Text;
    friend class Board;
public:
    Player(){} //when declaring vector without initializing
    Player(int id, bool split, string spid):Id(id), isSplit(split), SplitId(spid){}
    void initialize(int id, bool split, string spid)
    {
        Id = id;
        isSplit = split;
        SplitId=spid;
    }
};


#endif
