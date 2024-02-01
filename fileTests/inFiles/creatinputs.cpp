#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <random>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

vector<pair<string,int>> playersNames = {
        {"good", 20},
        {"Good", 17},
        {" good ", 3},
        {"Bad1", 1},
        {"#bad", 1},
        {"very Bad", 1},
        {"veryVeryVeryBad", 1}
    };
std::vector<std::pair<std::string,int>> cardsNames = {
        {"Barfight", 7},
        {"Dragon", 5},
        {"Gremlin", 12},
        {"Mana", 7},
        {"Merchant", 15},
        {"Treasure", 12},
        {"Well", 5},
        {"Witch", 10},
        {"Badfight", 1}
    };

vector<string> playerJobs = {
    "Ninja",
    "Warrior",
    "Healer"
};

string getPlaceCards(std::vector<std::pair<std::string,int>>& cards, int& isMerchant){
    if(cards.size() == 0) cards = cardsNames;
    int random_value = std::rand() % cards.size();
    string toReturn = cards[random_value].first;
    if(toReturn == "Merchant") isMerchant++;
    cards[random_value].second--;
    if(cards[random_value].second == 0) {
        cards.erase(cards.begin() + random_value);
    }
    return toReturn;
}

string getMerchant(){
    static int out = 3;
    if (out < 1) out = 3;
    out--;
    return to_string(out);
}

string getPlacePlayers(std::vector<std::pair<std::string,int>>& players, bool& b){
    b = 0;
    if(players.size() == 0) players = playersNames;
    int random_value = std::rand() % players.size();
    string toReturn = players[random_value].first;
    if(toReturn != "good" && toReturn != "Good" && toReturn != " good ") b = 1;
    players[random_value].second--;
    if(players[random_value].second == 0) {
        players.erase(players.begin() + random_value);
    }
    random_value = std::rand() % (playerJobs.size() + 1);
    toReturn += " ";
    if(random_value == playerJobs.size()){
        b = 1;
        int length = std::rand() % 20 + 1;
        for(int i = 0; i < length; i++){
            toReturn += ('!' + (rand() % ('z' - '!')));
        }
    }
    else{
        toReturn += playerJobs[random_value];
    }
    return toReturn;
}


void createTextFile(const string &filename, const string &input)
{
    std::ofstream file(filename);
    if(file){
        file << input;
    }
    file.close();
}

int main(){
    vector<pair<string,int>> tmpCardsNames = cardsNames;
    vector<pair<string,int>> tmpPlayersNames = playersNames;
    
    string name = "", input = "", nameDeck = "", nameInput = "";
    int isMerchant = 0;
    int num = 0;
    for (int deckLen = 4; deckLen < 33; deckLen += 4){
        for (int playerNum = 1; playerNum < 8; playerNum++){
            for (int i = 0; i < 49; i++){
                name = "test" + to_string(num);
                nameDeck = name + ".deck";
                ofstream deck(nameDeck);
                if(!deck) continue;
                for (int j = 0; j < deckLen; j++){
                    deck << getPlaceCards(tmpCardsNames, isMerchant) << endl;
                }
                deck.close();

                nameInput = name + ".in";
                ofstream input(nameInput);
                if(!input) continue;
                input << playerNum << endl;
                int playerTmp = playerNum;
                if(playerNum > 6 || playerNum < 2){
                    while(playerNum > 6 || playerNum < 2){
                        playerNum = std::rand() % 8;
                        input << playerNum << endl;
                    }
                }
                for (int j = 0; j < playerNum; j++){
                    bool b = 1;
                    while(b)
                        input << getPlacePlayers(tmpPlayersNames, b) << endl;
                }
                playerNum = playerTmp;
                for(int j = isMerchant * 100; j > 0; j--) {
                    input << getMerchant() << endl;
                }
                isMerchant = 0;
                input.close();
                num++;
                if(playerNum < 2 || playerNum > 6) break;
                if(deckLen < 5) break;
            }
            if(deckLen < 5) break;
        }
    }
    //no deck
    name = "test" + to_string(num) + ".in";
    input = "2\nShira Ninja\nTiser Healer";
    createTextFile(name, input);
    cout << "No deck in " << num << endl;
    num++;

    //bad Merchant
    name = "test" + to_string(num);
    nameDeck = name + ".deck";
    input = "Treasure\nTreasure\nMerchant\nTreasure\nDragon\nMerchant";
    createTextFile(nameDeck, input);
    nameInput = name + ".in";
    input = "2\nShira Ninja\nTiser Healer\n4\n@\n2";
    for(int i = 0 ; i < 100; i++){
        input += getMerchant();
        input += "\n";
    }
    createTextFile(nameInput, input);
    cout << "Bad Merchant in " << num << endl;
}