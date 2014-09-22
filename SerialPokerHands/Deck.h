#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Card{
private:
	string value;
	//string suit;
public:
	string suit;
	Card(){
		value = "";
		suit = "";
	}
	Card(string val, string st){
		value = val;
		suit = st;
	}
};

class Deck{
private:
vector<Card> deck;
public:
	
	Deck(){
		string values[13] = { "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king" };
		string suits[4] = { "spade", "heart", "diamond", "club" };
		for (int v = 0; v < 13; v++){
			for (int s = 0; s < 4; s++){
				Card temp = Card(values[v], suits[s]);
				deck.push_back(temp);		
			}
		}

	}
	vector<Card> getHand(){
		vector<Card> temp;
		random_shuffle(deck.begin(), deck.end());
		for (int i= 0; i < 5; i++){
			temp.push_back(deck[i]);
		}
		
		return temp;
	}
	
};
