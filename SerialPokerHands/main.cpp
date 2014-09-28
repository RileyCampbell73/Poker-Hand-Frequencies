#include"Deck.h"

#include <map>
#include <iostream>
using namespace std;



bool CheckPair(vector<int> hand){
	//hand pattern:
	//XXOOO OXXOO OOXXO OOOXX

	//put the array into a 2d array, making it easier to look at
	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}
	return  newHand[0][0] == newHand[1][0] || newHand[1][0] == newHand[2][0] || newHand[2][0] == newHand[3][0] || newHand[3][0] == newHand[4][0];
}
bool CheckTwoPair(vector<int> hand){
	//Hand Pattern
	//XXII0 0XXII 

	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}

	return newHand[0][0] == newHand[1][0] && newHand[2][0] == newHand[3][0] || newHand[1][0] == newHand[2][0] && newHand[3][0] == newHand[4][0];
}
bool CheckThreeofKind(vector<int> hand){
	//Hand Pattern
	//XXX00 0XXX0 00XXX

	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}

	return newHand[0][0] == newHand[1][0] && newHand[0][0] == newHand[2][0] || newHand[1][0] == newHand[2][0] && newHand[1][0] == newHand[3][0] || newHand[2][0] == newHand[3][0] && newHand[2][0] == newHand[4][0];

}

bool CheckFourofKind(vector<int> hand){
	//Hand Pattern
	//XXXX0 0XXXX

	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}

	return newHand[0][0] == newHand[1][0] && newHand[0][0] == newHand[2][0] && newHand[0][0] == newHand[3][0] || newHand[1][0] == newHand[2][0] && newHand[1][0] == newHand[3][0] && newHand[1][0] == newHand[4][0];

}

bool CheckFullHouse(vector<int> hand){
	//Hand Pattern
	//XXX00 00XXX

	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}
	return newHand[0][0] == newHand[1][0] && newHand[0][0] == newHand[2][0] && newHand[3][0] == newHand[4][0] || newHand[2][0] == newHand[3][0] && newHand[2][0] == newHand[4][0] && newHand[0][0] == newHand[1][0];

}

bool CheckStraight(vector<int> hand){
	//Hand Pattern
	//12345 54321

	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}

	return newHand[0][0] == newHand[1][0] + 1 && newHand[1][0] == newHand[2][0] + 1 && newHand[2][0] == newHand[3][0] + 1 && newHand[3][0] == newHand[4][0] + 1 
		|| newHand[0][0] == newHand[1][0] - 1 && newHand[1][0] == newHand[2][0] - 1 && newHand[2][0] == newHand[3][0] - 1 && newHand[3][0] == newHand[4][0] - 1;

}

bool CheckStraightFlush(vector<int> hand){
	//Hand Pattern
	//12345 54321
	//same suit

	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}

	return newHand[0][0] == newHand[1][0] + 1 && newHand[1][0] == newHand[2][0] + 1 && newHand[2][0] == newHand[3][0] + 1 && newHand[3][0] == newHand[4][0] + 1
		&& newHand[0][1] == newHand[1][1] && newHand[0][1] == newHand[2][1] && newHand[0][1] == newHand[3][1] && newHand[0][1] == newHand[4][1]
		|| newHand[0][0] == newHand[1][0] - 1 && newHand[1][0] == newHand[2][0] - 1 && newHand[2][0] == newHand[3][0] - 1 && newHand[3][0] == newHand[4][0] - 1
		&& newHand[0][1] == newHand[1][1] && newHand[0][1] == newHand[2][1] && newHand[0][1] == newHand[3][1] && newHand[0][1] == newHand[4][1];

}

bool CheckRoyalFlush(vector<int> hand) {
	// pattern:
	// XXXXX
	// A-10-J-Q-K

	//put the array into a 2d array, making it easier to look at
	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}
	
	// if the first card isn't an ace and the second card isn't a 10, we don't have a royal flush (ace is 1, 10 is 10)
	if (newHand[0][0] != 1 || newHand[1][0] != 10)
		return false;

	int suit = newHand[0][1];
	int temp = 0;

	// if every card doesn't have the same suit or doesn't increase from 1-13, we don't have a royal flush
	for( int i = 0; i < 5; ++i )
	{
		if( newHand[i][0] <= temp || newHand[i][1] != suit )
			return false;
		temp = newHand[i][0];
	}

	return true;
}

bool CheckFlush(vector<int> hand) {
	//put the array into a 2d array, making it easier to look at
	int newHand[5][2];
	for (int i = 0; i < 5; i++){
		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	}

	int suit = newHand[0][1];

	// if every card doesn't have the same suit we don't have a flush
	for( int i = 0; i < 5; ++i )
	{
		if( newHand[i][1] != suit )
			return false;
	}
	return true;
}

map<string, int> CheckFrequencies()
{
	map<string,int> frequencies;
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


	Deck cards;
	bool foundAll = false;

	do
	{
		vector<int> hand = cards.getHand();
		
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
		else if(CheckPair(hand))
			frequencies["onePair"] += 1;
		else
			frequencies["noPair"] += 1;

		typedef std::map<std::string, int>::iterator it_type;

		int foundCategories = 0;
		for(it_type iterator = frequencies.begin(); iterator != frequencies.end(); iterator++) {
			if( iterator->second != 0 )
				foundCategories ++;
			if( foundCategories == 10 )
				foundAll = true;
		}
		
	}while (!foundAll);

	return frequencies;
}

int main(){

	Deck cards;
	vector<int> hand = cards.getHand();

	bool foundRoyalFlush = false;

	/*do
	{
		vector<int> hand = cards.getHand();

		bool check = CheckPair();
	}while (!foundRoyalFlush);*/

	vector<int> premade; 
	/*premade.push_back(11);
	premade.push_back(101);
	premade.push_back(111);
	premade.push_back(121);
	premade.push_back(131);*/

	//this whole thing could have been done better.

	map<string,int> frequencies = CheckFrequencies();

	typedef std::map<std::string, int>::iterator it_type;
	for(it_type iterator = frequencies.begin(); iterator != frequencies.end(); iterator++) {
		cout << iterator->first << ": " << iterator->second << endl;
	}

	return 0;
}

