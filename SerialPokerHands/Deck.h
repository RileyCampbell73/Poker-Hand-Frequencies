#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <time.h>
using namespace std;

enum Value{
	ACE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING
};

enum Suit{
	SPADES,
	HEARTS,
	CLUBS,
	DIAMONDS
};



class Card{
private:
	Value value;
	Suit suit;
public:
	Card(){
		value = ACE;
		suit = SPADES;
	}
	Card(Value val, Suit st){
		value = val;
		suit = st;
	}
	Value getValue(){
		return value;
	}
	Suit getSuit(){
		return suit;
	}
	friend bool operator <( Card& first,  Card& second)
	{
		return first.getValue() < second.getValue();
	}

};

class Deck{
private:
	vector<Card> deck;
public:

	Deck(){
		//builds a deck using ints
		int values[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		int suits[4] = { 1, 2, 3, 4 };
		//loop takes both arrays and put all the values with the suits
		//so 1,1 for example is an ace of spades (1,1)
		//crude and there definatly a better way to do it. 
		//but this way will be the easiest in term of sorting and finding matches
		//for (int v = 0; v < 13; v++){
		//	for (int s = 0; s < 4; s++){
		//		string temp = to_string(values[v]) + to_string(suits[s]);
		//		deck.push_back(atoi(temp.c_str()));
		//	}
		//}

		for (int iVal = 0; iVal != 13; iVal++)
		{
			for (int iSuit = 0; iSuit != 4; iSuit++)
			{
				Card temp((Value)iVal, (Suit)iSuit);
				deck.push_back(temp);
			}
		}



	}

	//Shuffles the deck and then returns 5 'cards' from the top of the deck
	vector<Card> getHand(){
		vector<Card> hand;

		//shuffle the deck
		random_shuffle(deck.begin(),deck.end());
		//populate the hand with 5 cards off the deck
		for (int i= 0; i < 5; i++){
			hand.push_back(deck[i]);
		}
		
		//sort the hand
		sort(hand.begin(), hand.end());
		//hand.OrderBy(m = > m.Sort).ThenBy(m = > m.Name);
		return hand;
	}
	
};
