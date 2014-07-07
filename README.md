Blackjack
=========

A text based blackjack game written in C++ 
----------

## How to play
Initial screen will ask for user input to continue play (1), or exit the program (2).
If the players decide to play, then next prompt will ask for bet from each player sequentially.
Once bets are done, the dealer deals the card and the next prompt shows board condition (delars and players card).
The dealer will go sequentially to each player asking for action. Each player can either hit(H), stand(S), double down(D) or split to two bets(S). The option for double down and split will only be available if the situation permits. Once all player plays the game, the game will show the final standing in terms of chips available to each player and ask whether to play or exit.

## Game Rules
1. **Splitting :** Unlimited number of splitting is permitted as long as the player has money and the two cards have the same blackjack value.
2. **Payout :** The pay out is 1:1 except for blackjack in which case the payout is 3:2.
3. **Soft 17 Rule:** The dealer will stand on soft 17.
4. **Number of Players:** Any number of player can play the game. The default is one player. The number of player is defined before the game starts (See Setup Options below).


## Setup Options
A few setup variables are defined at the beginning of 'main.cpp' files. 
* **NumPlayer** : Sets the number of players playing the game. Default is 1.
* **NumDeck** : Sets the number of deck of cards in the shoe. Default is 4.
* **isRandomSeed** : Sets the seed for random number generator to random, when 'true'. When 'false', the random number generator use the variable 'Seed' to determine the seed. Default is true.
* **Seed** : When random number generator use fixed seed, it use this variable to get the initial seed value. Default is 100.
* **initialAccountValue** : Initial number of chips available to each player. Default is 100.
* **useTextSymbol** : When false, use unicode symbol (e.g. &#9829;,&#9824;,&#9827;,&#9830;) to output the suits of a card. When true, use text (e.g. Hearts, Spades, Clubs, Diamonds) to output the suits of a card.

## Supported Environment
The program is written, compiled and tested using Xcode environment version 5.1.1. The 'Executable/OSX' folder contains the executable file created using Xcode.

The program is also compiled and tested using g++ in Windows 8 environment using Netbeans IDE with cygwin 1.7.30. The 'Executable/Windows' folder contains the executable file created using cygwin.

The program is also compiled and tested using g++ in Windows 8 using Codelite IDE with MinGW version 4.8.1. 

## Known Issue
* An issue is found with the card suit symbol (e.g. hearts, spades etc.) output when the program is compiled using MinGW 4.8.1 using Codelite IDE. It is advised to set the 'useTextSymbol' variable to true when using this environment.
* The program require c++11 options. Therefore, when compiling with Codelite or Netbeans in Windows environment the compiler option '-std=c++11' should be added.