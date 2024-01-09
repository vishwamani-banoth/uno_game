#include <bits/stdc++.h>
#include "Simulator.h"
using namespace std;

Simulator::Simulator(/* args */)
{
}

Simulator::Simulator(int noOfPlayers,int noOfColors,int noOfNumbers)
{
    for(int i=0;i<noOfPlayers;i++){
        players.push_back(new Player(i));
    }
    cardDeck=new CardDeck(noOfNumbers,noOfColors);
}
int Simulator::reversePlayers(int idx){
    // std::cout << std::setfill('-') << std::setw(38) << '\n';
    cout<<" direction is reversed 🔁"<<endl;
    std::cout << std::setfill('-') << std::setw(38) << '\n';
    reverse(players.begin(),players.end());
    if(idx==0){
        return 0;
    }
    return players.size()-idx;
    
}
void Simulator::giveCards(Player* player,int noofCards){
    int n=noofCards;
    while(n--){
        player->takeCard(cardDeck->getCard());
    }
    if(noofCards==1){
        cout<<"player With ID: "<<player->getId()<<" took "<<noofCards<< " card 😂😂"<<endl;
    }
    else
    { 
        cout<<"player With ID: "<<player->getId()<<" took "<<noofCards<< " cards 😂😂"<<endl;
    }
    std::cout << std::setfill('-') << std::setw(38) << '\n';

}
void Simulator::simulateManually(){
    int noOfPlayers=players.size();
    bool plusFourPlayed=false;
    bool plusTwoPlayed=false;
    cardDeck->shuffle(10000);
    distributeCards(7);
    Card* topCard=cardDeck->getCard();
    while(topCard!=NULL && topCard->isPlus4() || topCard->isWild()){
        topCard=cardDeck->getCard();
    }
    cardDeck->putCardInDiscardPile(topCard);
    int i=0;
    while(true){
        topCard=cardDeck->getTopCard();
        if(plusFourPlayed){
            plusFourPlayed=false;
            giveCards(players[i],4);
            i=(i+1)%noOfPlayers;
            continue;
        }
        if(plusTwoPlayed){
            plusTwoPlayed=false;
            giveCards(players[i],2);
            i=(i+1)%noOfPlayers;
            continue;
        }
        Card* playedCard=players[i]->putCardManual(topCard);
        cout<<"Played Card : ";
        if(playedCard){
            playedCard->show();
        } 
        else cout<<"No Card Played";
        cout<<endl;
        if(playedCard==NULL){
            giveCards(players[i],1);
            cout<<"player with id : "<<players[i]->getId()<<" continuing turn "<<endl;
            playedCard=players[i]->putCardManual(topCard);
            if(playedCard) playedCard->show();
            else cout<<"No Card Played";
            cout<<endl;
        }
        if(playedCard!=NULL && playedCard->isPlus4()){
            plusFourPlayed=true;
            string chosenColor=getColorChoice();
            playedCard->setColor(chosenColor);
        }
        if(playedCard!=NULL && playedCard->isWild()){
            string chosenColor=getColorChoice();
            playedCard->setColor(chosenColor);
        }
        if(playedCard!=NULL && playedCard->isPlus2()){
            plusTwoPlayed=true;
        }
        if (playedCard!=NULL && playedCard->isSkip())
        {
            if(CheckPlayerWon(players[i])){
                break;
            }
            // std::cout << std::setfill('-') << std::setw(38) << '\n';
            cout<<"Player "<<players[(i+1)%noOfPlayers]->getId()<<"'s turn Skipped 🚫"<<endl;
            std::cout << std::setfill('-') << std::setw(38) << '\n';
            i=(i+2)%noOfPlayers;
        }
        if (playedCard!=NULL && playedCard->isReverse())
        {
            if(CheckPlayerWon(players[i])){
                break;
            }
            i=reversePlayers(i);
        }
        if(playedCard!=NULL){
            if(cardDeck->getTopCard()->isPlus4() ||  cardDeck->getTopCard()->isWild()){
                cardDeck->getTopCard()->setColor("NULL");
            }

            cardDeck->putCardInDiscardPile(playedCard);
            if(playedCard->isSkip()||playedCard->isReverse()){
                continue;    
            }
        }
        if(players[i]->didWin()){
            cout<<"Player with ID "<<players[i]->getId()<<" Won the match 🔥🔥🔥"<<endl;
            break;
        }
        if(CheckPlayerWon(players[i])){
            break;
        }
        std::cout << std::setfill('-') << std::setw(38) << '\n';
        i=(i+1)%noOfPlayers;
    }

}
void Simulator::simulateAutomatically(){
    int noOfPlayers=players.size();
    bool plusFourPlayed=false;
    bool plusTwoPlayed=false;
    cardDeck->shuffle(10000);
    distributeCards(7);
    Card* topCard=cardDeck->getCard();
    while(topCard!=NULL && topCard->isPlus4() || topCard->isWild()){
        topCard=cardDeck->getCard();
    }
    cardDeck->putCardInDiscardPile(topCard);
    int i=0;
    while(true){
        topCard=cardDeck->getTopCard();
        if(plusFourPlayed){
            plusFourPlayed=false;
            giveCards(players[i],4);
            i=(i+1)%noOfPlayers;
            continue;
        }
        if(plusTwoPlayed){
            plusTwoPlayed=false;
            giveCards(players[i],2);
            i=(i+1)%noOfPlayers;
            continue;
        }
        Card* playedCard=players[i]->putCardAutomatically(topCard);
        cout<<"Played Card : ";
        if(playedCard){
            playedCard->show();
        } 
        else cout<<"No Card Played";
        cout<<endl;
        if(playedCard==NULL){
            giveCards(players[i],1);
            cout<<"player with id : "<<players[i]->getId()<<" continuing turn "<<endl;
            playedCard=players[i]->putCardAutomatically(topCard);
            if(playedCard) playedCard->show();
            else cout<<"No Card Played";
            cout<<endl;
        }
        if(playedCard!=NULL && playedCard->isPlus4()){
            plusFourPlayed=true;
            string chosenColor=getColorChoiceAutomatically();
            playedCard->setColor(chosenColor);
        }
        if(playedCard!=NULL && playedCard->isWild()){
            string chosenColor=getColorChoiceAutomatically();
            playedCard->setColor(chosenColor);
        }
        if(playedCard!=NULL && playedCard->isPlus2()){
            plusTwoPlayed=true;
        }
        if (playedCard!=NULL && playedCard->isSkip())
        {
            if(CheckPlayerWon(players[i])){
                break;
            }
            // std::cout << std::setfill('-') << std::setw(38) << '\n';
            cout<<"Player "<<players[(i+1)%noOfPlayers]->getId()<<"'s turn Skipped 🚫"<<endl;
            std::cout << std::setfill('-') << std::setw(38) << '\n';
            i=(i+2)%noOfPlayers;
        }
        if (playedCard!=NULL && playedCard->isReverse())
        {
            if(CheckPlayerWon(players[i])){
                break;
            }
            i=reversePlayers(i);
        }
        if(playedCard!=NULL){
            if(cardDeck->getTopCard()->isPlus4() ||  cardDeck->getTopCard()->isWild()){
                cardDeck->getTopCard()->setColor("NULL");
            }

            cardDeck->putCardInDiscardPile(playedCard);
            if(playedCard->isSkip() || playedCard->isReverse()){
                continue;    
            }
        }
        if(CheckPlayerWon(players[i])){
            break;
        }
        i=(i+1)%noOfPlayers;
    }

}
bool Simulator::CheckPlayerWon(Player* player){
    if(player->didWin()){
        cout<<"Player with ID "<<player->getId()<<" Won the match 🔥🔥🔥"<<endl;
        return true;
    }
    cout<<"Player "<<player->getId()<<"'s Remaining cards are "<<player->getNoOfCardsRemaining()<<endl;
    cout<<"Player "<<player->getId()<<"'s turn over"<<endl;
    std::cout << std::setfill('-') << std::setw(38) << '\n';
    return false;
}
void Simulator::distributeCards(int noOfCards){
    for(auto player:players){
        for(int i=0;i<noOfCards;i++){
            player->takeCard(cardDeck->getCard());
        }
    }
}
string Simulator::getColorChoice(){
    vector<string> colors=cardDeck->getColors();
    cout<<"Color Choices: "<<endl;
    for(int i=0;i<colors.size();i++){
        cout<<"choice "<<i+1<<" :";
        cout<<colors[i]<<endl;
    }
    int choice;
    cout<<"Select Color Choices: ";
    cin>>choice;
    while(choice-1>colors.size()|| choice-1<0){
        cout<<"Wrong Choice"<<endl;
        cout<<"Select Correct colors Choice:";
        cin>>choice;
    }
    cout<<endl;
    return colors[choice-1];
}
string Simulator::getColorChoiceAutomatically(){
    vector<string> colors=cardDeck->getColors();
    cout<<"Color Choices: "<<endl;
    for(int i=0;i<colors.size();i++){
        cout<<"choice "<<i+1<<" :";
        cout<<colors[i]<<endl;
    }
    cout<<"Select Color Choices: ";
    random_device rd;
    uniform_int_distribution<int> distribution(1,colors.size());
    int choice=distribution(rd);
    cout<<choice<<endl;
    return colors[choice-1];
}
Simulator::~Simulator()
{
}
