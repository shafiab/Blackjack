//
//  Account.h
//  Blackjack
//
//  Created by Shafi Bashar on 7/6/14.
//  Copyright (c) 2014 Shafi Bashar. All rights reserved.
//

#ifndef Blackjack_Account_h
#define Blackjack_Account_h

class Account
{
    double PlayerChips; // chips can be fractional
    friend class Text;
public:
    int initialBet; //bet cannot be fractional
    void initialize(double c, int b)
    {
        PlayerChips = c;
    }
};


#endif
