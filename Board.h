//
//  Board.h
//  Blackjack
//
//  Created by Shafi Bashar on 7/6/14.
//  Copyright (c) 2014 Shafi Bashar. All rights reserved.
//

#ifndef Blackjack_Board_h
#define Blackjack_Board_h
class Player;
class Shoe;
class Text;

class Board
{
    int NumDeck;
    int NumPlayer;
    Shoe myShoe;
    unsigned int Seed;
public:
    // variables
    vector<Player> myP;
    vector<int> DealerCard;
    
    // constructor
    Board(int nplayer, int ndeck, unsigned int s):NumPlayer(nplayer), NumDeck(ndeck), Seed(s),myShoe(ndeck, s){}
    
    // setup/initialization functions
    void createBoard(); // create shoe
    void initializeBoard(Text&); // initialize players and perform card dealing
    bool initialCheckDealer(vector<Outcome>&result); // dealer checks for Blackjack
    void initialCheckPlayer(vector<Outcome>&result); // player checks for Blackjack

    // helper function
    int total(const vector<int>&); // total (best) value of the cards of player/dealer
    int value(const int&); // blackjack value of a particular card
    Outcome checkResult(const vector<int>&, const vector<int>&); // compare results in case of NONE

    
    // game function
    void runGame(Text&, vector<Outcome>&); // main function to run the game
    Outcome dealersTurn(); // dealers move
    Outcome playersTurn(Player& myP,Text& myText, bool&); // players move
    void performSplitOperation(vector<Player>&myP, vector<Player>::iterator& it); // special operation in case of splitting
};

void Board::createBoard()
{
    myShoe.CreateShoe();
}

void Board::initializeBoard(Text& myText)
{
    myP.resize(NumPlayer);
    for (int i=0;i<NumPlayer;i++)
    {
        myP[i].initialize(i,false,"0");
        myP[i].Card.clear();
        myP[i].playerBet = myText.myA[i].initialBet;
    }
    
    DealerCard.clear();
    for (int i=0;i<NumPlayer;i++)
    {
        if (myText.playerStatus[i])  myP[i].Card.push_back(myShoe.pullCard());
        
    }
    DealerCard.push_back(myShoe.pullCard());
    for (int i=0;i<NumPlayer;i++)
    {
        if (myText.playerStatus[i])  myP[i].Card.push_back(myShoe.pullCard());
    }
    DealerCard.push_back(myShoe.pullCard());
}

bool Board::initialCheckDealer(vector<Outcome>&result)
{
    if (total(DealerCard)==BJ)
    {
        for (int i=0;i<NumPlayer;i++)
        {
            if (total(myP[i].Card)==BJ)
                result.push_back(PUSH);
            else
                result.push_back(DEALER_BJ);
        }
        return true;
    }
    
    return false;
}

void Board::initialCheckPlayer(vector<Outcome>&result)
{
    for (int i=0;i<NumPlayer;i++)
    {
        if (total(myP[i].Card)==BJ)
            result.push_back(PLAYER_BJ);
        else
            result.push_back(NONE);
    }
}

int Board::value(const int& card)
{
    return VALUE[card%NUM_CARD_DECK%NUM_CARD_SUIT];
}

int Board::total(const vector<int>& card)
{
    int total = 0;
    int val;
    int NumAce = 0;
    for (int i=0;i<card.size();i++)
    {
        val = value(card[i]);
        if (val==11)
            NumAce++;
        else
            total += val;
    }
    if (NumAce>0)
    {
        if (NumAce>1)
        {
            total += (NumAce-1);
            NumAce = 1;
        }
        if (NumAce==1)
        {
            if (total + 11 > TwentyOne)
                total += 1;
            else
                total += 11;
        }
    }
    return total;
}

void Board::runGame(Text& myText, vector<Outcome>&Result)
{
    // print initial board
    myText.printLine("Dealer finished dealing card...current board status:", true);
    myText.printDealerCard(DealerCard, true);
    for (vector<Player>::iterator it=myP.begin();it!=myP.end();it++)
        myText.printPlayerCard(*it);
    
    // perform check to see if dealer/player has blackjack
    bool isDelaerBJ = initialCheckDealer(Result);
    if (!isDelaerBJ) initialCheckPlayer(Result);
    

    bool isDealerTurn = false; // player made first move
    
    unsigned int counter = 0;
    vector<Player>::iterator it = myP.begin();

    while(it!=myP.end()) // loop over each player
    {
        myText.addBlankLine(2);
        myText.printPlayerCard(*it);
        if (Result[counter] != PLAYER_BJ) // if PLAYER_BJ, skip
        {
            bool isSplit;
            Result[counter] = playersTurn(*it, myText, isSplit); // players move
            if (isSplit) // create additional player stucture in case of splitting
            {
                performSplitOperation(myP,it);
                Result.insert(Result.begin()+counter+1,NONE); // create additional Result
                // do not update iterator and counter
            }
            else
            {
                if (Result[counter]==PLAYER_BUST) myText.printResult(Result[counter]);
                if (Result[counter]==NONE) isDealerTurn = true;
                counter++; // update counter
                it++; //update iterator
            }
        }
        else
        {
            counter++; //update counter
            it++; //update iterator
        }
    }
    
    // dealers turn
    Outcome dealerResult=NONE;
    if(isDealerTurn)
    {
        dealerResult =  dealersTurn();
    }
    
    
    // print and update result
    myText.printDealerCard(DealerCard, false);
    for (int i=0;i<Result.size();i++)
    {
        if ((myText.playerStatus[myP[i].Id]) && (Result[i]!=PLAYER_BUST))
        {
            myText.printPlayerCard(myP[i]);
            if (Result[i]!=PLAYER_BJ)
            {
                if (dealerResult==DEALER_BUST)
                    Result[i]=DEALER_BUST;
                else if(Result[i]==NONE)
                    Result[i]= checkResult(myP[i].Card, DealerCard);
            }
            myText.printResult(Result[i]);
        }
    }
    
    // update accounting
    for (int i=0;i<Result.size();i++)
    {
        myText.updateAccounting(myP[i].Id,myP[i].playerBet, Result[i]);
    }
    
}

Outcome Board::dealersTurn()
{
    // dealer stand on soft 17
    int Total = total(DealerCard);
    while (Total < 17)
    {
        DealerCard.push_back(myShoe.pullCard()); // dealer takes a card
        Total = total(DealerCard);
    }
    if (Total > TwentyOne)
        return DEALER_BUST;
    else
        return NONE;
}

Outcome Board::playersTurn(Player& myP,Text& myText, bool& isSplit)
{
    Outcome result = NONE; // initialize result
    bool isSplitPossible = ((myP.Card.size()==2) && ( value(myP.Card[0])==value(myP.Card[1]) ) );
    isSplit = false;
    bool isFirstTurn = true;
    
    bool isPlayerTurn = true;
    while(isPlayerTurn)
    {
        PlayerAction playerInput = myText.playerInput(myP, isFirstTurn, isSplitPossible);
        
        // after first turn, set to false
        isFirstTurn = false;
        isSplitPossible = false;
        
        switch(playerInput)
        {
            case HIT:
                myP.Card.push_back(myShoe.pullCard()); // add another card to player
                myText.printPlayerCard(myP);
                if (total(myP.Card)>TwentyOne)
                {
                    result = PLAYER_BUST;
                    isPlayerTurn = false;
                }
                break;
            case STAND:
                isPlayerTurn = false;
                break;
            case DOUBLE:
                isPlayerTurn = false;
                myP.Card.push_back(myShoe.pullCard()); // add another card to player
                myText.printPlayerCard(myP);
                if (total(myP.Card)>TwentyOne)
                    result = PLAYER_BUST;
                break;
            case SPLIT:
                isSplit = true;
                isPlayerTurn = false;
                break;
            case NO:
                isPlayerTurn = false;
                break;
        }
    }
    return result;
}


void Board::performSplitOperation(vector<Player>&myP, vector<Player>::iterator& it)
{
    it = myP.insert(it+1, Player(it->Id,true,it->SplitId+"-2"));
    it--; // to get back to it
    (it+1)->playerBet = it->playerBet; //additional player bet to second split
    (it+1)->Card.push_back(it->Card[1]);
    
    it->SplitId =it->SplitId+"-1";
    it->isSplit = true;
    it->Card[1] = myShoe.pullCard();
    (it+1)->Card.push_back(myShoe.pullCard());
}


Outcome Board::checkResult(const vector<int>& PCard, const vector<int>&DCard)
{
    if (total(PCard) > total(DCard))
        return PLAYER_WIN;
    else if (total(PCard) == total(DCard))
        return PUSH;
    else
        return DEALER_WIN;
}


#endif
