#include"Deck.h"

#include <map>
#include <iostream>
#include <iomanip>
using namespace std;

unsigned int total = 0;


bool CheckPair(vector<Card> hand){
	//hand pattern:
	//XXOOO OXXOO OOXXO OOOXX

	return  hand[0].getValue() == hand[1].getValue() || hand[1].getValue() == hand[2].getValue() || hand[2].getValue() == hand[3].getValue() || hand[3].getValue() == hand[4].getValue();
}
bool CheckTwoPair(vector<Card> hand){
	//Hand Pattern
	//XXII0 0XXII 

	return hand[0].getValue() == hand[1].getValue() && hand[2].getValue() == hand[3].getValue() || hand[1].getValue() == hand[2].getValue() && hand[3].getValue() == hand[4].getValue();
}
bool CheckThreeofKind(vector<Card> hand){
	//Hand Pattern
	//XXX00 0XXX0 00XXX

	return hand[0].getValue() == hand[1].getValue() && hand[0].getValue() == hand[2].getValue() || hand[1].getValue() == hand[2].getValue() && hand[1].getValue() == hand[3].getValue() || hand[2].getValue() == hand[3].getValue() && hand[2].getValue() == hand[4].getValue();

}

bool CheckStraight(vector<Card> hand){
	//Hand Pattern
	//12345 54321

	return hand[0].getValue() == hand[1].getValue() + 1 && hand[1].getValue() == hand[2].getValue() + 1 && hand[2].getValue() == hand[3].getValue() + 1 && hand[3].getValue() == hand[4].getValue() + 1
		|| hand[0].getValue() == hand[1].getValue() - 1 && hand[1].getValue() == hand[2].getValue() - 1 && hand[2].getValue() == hand[3].getValue() - 1 && hand[3].getValue() == hand[4].getValue() - 1;

}

bool CheckFlush(vector<Card> hand) {
	int suit = hand[0].getSuit();

	// if every card doesn't have the same suit we don't have a flush
	for (int i = 0; i < 5; ++i)
	{
		if (hand[i].getSuit() != suit)
			return false;
	}
	return true;
}

bool CheckFullHouse(vector<Card> hand){
	//Hand Pattern
	//XXX00 00XXX

	return hand[0].getValue() == hand[1].getValue() && hand[0].getValue() == hand[2].getValue() && hand[3].getValue() == hand[4].getValue()
		|| hand[2].getValue() == hand[3].getValue() && hand[2].getValue() == hand[4].getValue() && hand[0].getValue() == hand[1].getValue();

}

bool CheckFourofKind(vector<Card> hand){
	//Hand Pattern
	//XXXX0 0XXXX

	return hand[0].getValue() == hand[1].getValue() && hand[0].getValue() == hand[2].getValue() && hand[0].getValue() == hand[3].getValue()
		|| hand[1].getValue() == hand[2].getValue() && hand[1].getValue() == hand[3].getValue() && hand[1].getValue() == hand[4].getValue();

}

bool CheckStraightFlush(vector<Card> hand){
	//Hand Pattern
	//12345 54321
	//same suit

	return hand[0].getValue() == hand[1].getValue() + 1 && hand[1].getValue() == hand[2].getValue() + 1 && hand[2].getValue() == hand[3].getValue() + 1 && hand[3].getValue() == hand[4].getValue() + 1
		&& hand[0].getSuit() == hand[1].getSuit() && hand[0].getSuit() == hand[2].getSuit() && hand[0].getSuit() == hand[3].getSuit() && hand[0].getSuit() == hand[4].getSuit()
		|| hand[0].getValue() == hand[1].getValue() - 1 && hand[1].getValue() == hand[2].getValue() - 1 && hand[2].getValue() == hand[3].getValue() - 1 && hand[3].getValue() == hand[4].getValue() - 1
		&& hand[0].getSuit() == hand[1].getSuit() && hand[0].getSuit() == hand[2].getSuit() && hand[0].getSuit() == hand[3].getSuit() && hand[0].getSuit() == hand[4].getSuit();

}

bool CheckRoyalFlush(vector<Card> hand) {
	// pattern:
	// XXXXX
	// A-10-J-Q-K
	Suit s = hand[0].getSuit();

	return hand[0].getValue() == ACE && hand[1].getValue() == TEN && hand[2].getValue() == JACK && hand[3].getValue() == QUEEN && hand[4].getValue() == KING
		&& hand[1].getSuit() == s && hand[2].getSuit() == s && hand[3].getSuit() == s && hand[4].getSuit() == s;

}


map<string, int> frequencies;

bool CheckFrequencies()
{
	



	Deck cards;
	bool foundAll = false;

		vector<Card> hand = cards.getHand();

		if(CheckRoyalFlush(hand))
			frequencies["royalFlush"] += 1;
		else if(CheckStraightFlush(hand))
			frequencies["straightFlush"] += 1;
		else if(CheckFourofKind(hand))
			frequencies["fourOfAKind"] += 1;
		else if(CheckFullHouse(hand))
			frequencies["fullHouse"] += 1;
		else if(CheckFlush(hand))
			frequencies["flush"] += 1;
		else if(CheckStraight(hand))
			frequencies["straight"] += 1;
		else if(CheckThreeofKind(hand))
			frequencies["threeOfAKind"] += 1;
		else if(CheckTwoPair(hand))
			frequencies["twoPair"] += 1;
		else if (CheckPair(hand))
			frequencies["onePair"] += 1;
		else
			frequencies["noPair"] += 1;


	//	//int foundCategories = 0;
	//	//for(it_type iterator = frequencies.begin(); iterator != frequencies.end(); iterator++) {
	//	//	if( iterator->second != 0 )
	//	//		foundCategories ++;
	//	//	if( foundCategories == 9 )
	//	//		foundAll = true;
	//	//}
	//	//if (frequencies["royalFlush"] > 0)
	//		//foundAll = true;
	//	


	return false;
}

int main(int argc, char* argv[]){
	Deck cards;
	vector<Card> hand = cards.getHand();
	int count = 0;

	frequencies["noPair"] = 0;
	frequencies["onePair"] = 0;
	frequencies["twoPair"] = 0;
	frequencies["threeOfAKind"] = 0;
	frequencies["straight"] = 0;
	frequencies["flush"] = 0;
	frequencies["fullHouse"] = 0;
	frequencies["fourOfAKind"] = 0;
	frequencies["straightFlush"] = 0;
	frequencies["royalFlush"] = 0;

	srand((unsigned int)time(0));

	do{
		count++;
		if (CheckFrequencies()){
			break;
		}
	} while (frequencies["royalFlush"] <= 0);


	cout << setw(64) << right << "Poker Hand Frequency Simulation [SERIAL Version]" << endl;
	cout << setw(60) << right << "================================================================" << endl;
	cout << setw(16) << right << "Hand Type" << setw(18) << "Frequency" << setw(30) << "Relative Frequency (%)" << endl;
	cout << setw(60) << right << "----------------------------------------------------------------" << endl;
	cout << setw(16) << right << "No Pair" << setw(18) << frequencies["noPair"] << setw(30) << setprecision(6) << (frequencies["noPair"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "One Pair" << setw(18) << frequencies["onePair"] << setw(30) << setprecision(6) << (frequencies["onePair"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Two Pair" << setw(18) << frequencies["twoPair"] << setw(30) << setprecision(6) << (frequencies["twoPair"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Three of a Kind" << setw(18) << frequencies["threeOfAKind"] << setw(30) << setprecision(6) << (frequencies["threeOfAKind"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Straight" << setw(18) << frequencies["straight"] << setw(30) << setprecision(6) << (frequencies["straight"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Flush" << setw(18) << frequencies["flush"] << setw(30) << setprecision(6) << (frequencies["flush"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Full House" << setw(18) << frequencies["fullHouse"] << setw(30) << setprecision(6) << (frequencies["fullHouse"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Four of a Kind" << setw(18) << frequencies["fourOfAKind"] << setw(30) << setprecision(6) << (frequencies["fourOfAKind"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Straight Flush" << setw(18) << frequencies["straightFlush"] << setw(30) << setprecision(6) << (frequencies["straightFlush"] / (count * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Royal Flush" << setw(18) << frequencies["royalFlush"] << setw(30) << setprecision(6) << (frequencies["royalFlush"] / (count * 1.0)) * 100 << endl;
	cout << setw(60) << right << "----------------------------------------------------------------" << endl;
	cout << setw(16) << right << "Hands Generated: " << setw(18) << count << endl;
	cout << setw(60) << right << "----------------------------------------------------------------" << endl;



	return 0;
}

