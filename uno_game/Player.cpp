#include <bits/stdc++.h>
#include <random>

#include "Player.h"
using namespace std;
Player::Player(){

}
Player::Player(int ID){
    id=ID;
}
Card* Player::putCardAutomatically(Card* topCard){
    vector<Card*> filteredCards=filter(topCard);
    cout<<"Player "<<id<<"'s turn"<<endl;
    cout<<"TopCard  : ";
    topCard->show();cout<<endl;
    int choice=getCardChoiceAutomatic(filteredCards);
    if(choice==-1){
        return NULL;
    }
    Card* selectedCard=filteredCards[choice];
    // cout<<"before erasing"<<endl;
    cards.erase(filteredCards[choice]);
    // cout<<"after Erasing "<<endl;
    return selectedCard;
}
Card* Player::putCardManual(Card* topCard){
    cout<<"Player "<<id<<"'s turn"<<endl;
    cout<<"TopCard  : ";
    topCard->show();cout<<endl;
    vector<Card*> filteredCards=filter(topCard);
    int choice=getCardChoice(filteredCards);
    if(choice==-1){
        return NULL;
    }
    Card* selectedCard=filteredCards[choice];
    // cout<<"before erasing"<<endl;
    cards.erase(filteredCards[choice]);
    // cout<<"after Erasing "<<endl;
    return selectedCard;
}
vector<Card*> Player::filter(Card* topCard){
    vector<Card*> filteredCards;
    for(auto card:cards){
        if(card->isWild()){
                filteredCards.push_back(card);
        }
        else if(topCard->isReverse()&& card->isReverse()){
                filteredCards.push_back(card);
        }

        else if(topCard->isSkip()&& card->isSkip()){
            filteredCards.push_back(card);
        }
        else if(topCard->isPlus2()&& card->isPlus2()){
            filteredCards.push_back(card);
        }
        else if(topCard->getNumber()==card->getNumber() && topCard->getNumber()!=-1 ){
            filteredCards.push_back(card);
        }
        else if((topCard->getColor()==card->getColor() ) && topCard->getColor()!="NULL" ){
                filteredCards.push_back(card);
        }
        

    }
    for(auto card:cards){
        if(filteredCards.empty() && card->isPlus4()){
            filteredCards.push_back(card);
        }
    }
    for(auto card:cards){
        int random = rand() % 10;
        if(random==9 && card->isPlus4()){
            filteredCards.push_back(card);
        }
    }
    return filteredCards;
}
void Player::takeCard(Card* inputCard){
    cards.insert(inputCard);
}
bool Player::didWin(){
    return cards.size()==0;
}
int Player::getId(){
    return id;
}
int Player::getNoOfCardsRemaining(){
    return cards.size();
}
 
int Player::getCardChoice(vector<Card*> filteredCards){
    if(filteredCards.size()==0){
        return -1;
    }
    for(int i=0;i<filteredCards.size();i++){
        cout<<"choice "<<i+1<<" : ";
        filteredCards[i]->show();
        cout<<endl;
    }
    int choice;
    cout<<"Select Card Choice: ";
    cin>>choice;
    while(choice-1>=filteredCards.size()||choice-1<0){
        cout<<"Wrong Choice"<<endl;
        cout<<"Select Correct Card Choice:";
        cin>>choice;
    }
    return choice-1;
}
int Player::getCardChoiceAutomatic(vector<Card*> filteredCards){
    if(filteredCards.size()==0){
        return -1;
    }
    for(int i=0;i<filteredCards.size();i++){
        cout<<"choice "<<i+1<<" : ";
        filteredCards[i]->show();
        cout<<endl;
    }
    //random choice generator
    random_device rd;
    uniform_int_distribution<int> distribution(1,filteredCards.size());
    int choice=distribution(rd);
    cout<<"Select Card Choice: ";
    cout<<choice<<endl;
    return choice-1;
}

Player::~Player(){
    for(auto card:cards){
        delete card;
    }
}