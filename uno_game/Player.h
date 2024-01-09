#include<bits/stdc++.h>
#ifndef PLAYER_H
#define PLAYER_H
#include"Card.h"
using namespace std;
class Player
{
private:
    unordered_set<Card*> cards; 
    int id;
public:
    Player();
    Player(int);
    Card* putCardManual(Card*);
    Card* putCardAutomatically(Card*);
    vector<Card*> filter(Card*);
    void takeCard(Card*);
    bool didWin();
    int getCardChoice(vector<Card*>);
    int getId();
    int getNoOfCardsRemaining();
    int getCardChoiceAutomatic(vector<Card*>);
    ~Player();
};
#endif
