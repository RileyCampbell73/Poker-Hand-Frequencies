#include"Deck.h"

#include <map>
#include <iostream>
#include <iomanip>
using namespace std;

unsigned int total = 0;


bool CheckPair(int hand[5][2]){
	//hand pattern:
	//XXOOO OXXOO OOXXO OOOXX

	return  hand[0][0] == hand[1][0] || hand[1][0] == hand[2][0] || hand[2][0] == hand[3][0] || hand[3][0] == hand[4][0];
}
bool CheckTwoPair(int hand[5][2]){
	//Hand Pattern
	//XXII0 0XXII 

	return hand[0][0] == hand[1][0] && hand[2][0] == hand[3][0] || hand[1][0] == hand[2][0] && hand[3][0] == hand[4][0];
}
bool CheckThreeofKind(int hand[5][2]){
	//Hand Pattern
	//XXX00 0XXX0 00XXX

	return hand[0][0] == hand[1][0] && hand[0][0] == hand[2][0] || hand[1][0] == hand[2][0] && hand[1][0] == hand[3][0] || hand[2][0] == hand[3][0] && hand[2][0] == hand[4][0];

}

bool CheckFourofKind(int hand[5][2]){
	//Hand Pattern
	//XXXX0 0XXXX

	return hand[0][0] == hand[1][0] && hand[0][0] == hand[2][0] && hand[0][0] == hand[3][0] || hand[1][0] == hand[2][0] && hand[1][0] == hand[3][0] && hand[1][0] == hand[4][0];

}

bool CheckFullHouse(int hand[5][2]){
	//Hand Pattern
	//XXX00 00XXX

	return hand[0][0] == hand[1][0] && hand[0][0] == hand[2][0] && hand[3][0] == hand[4][0] || hand[2][0] == hand[3][0] && hand[2][0] == hand[4][0] && hand[0][0] == hand[1][0];

}

bool CheckStraight(int hand[5][2]){
	//Hand Pattern
	//12345 54321

	return hand[0][0] == hand[1][0] + 1 && hand[1][0] == hand[2][0] + 1 && hand[2][0] == hand[3][0] + 1 && hand[3][0] == hand[4][0] + 1 
		|| hand[0][0] == hand[1][0] - 1 && hand[1][0] == hand[2][0] - 1 && hand[2][0] == hand[3][0] - 1 && hand[3][0] == hand[4][0] - 1;

}

bool CheckStraightFlush(int hand[5][2]){
	//Hand Pattern
	//12345 54321
	//same suit

	return hand[0][0] == hand[1][0] + 1 && hand[1][0] == hand[2][0] + 1 && hand[2][0] == hand[3][0] + 1 && hand[3][0] == hand[4][0] + 1
		&& hand[0][1] == hand[1][1] && hand[0][1] == hand[2][1] && hand[0][1] == hand[3][1] && hand[0][1] == hand[4][1]
		|| hand[0][0] == hand[1][0] - 1 && hand[1][0] == hand[2][0] - 1 && hand[2][0] == hand[3][0] - 1 && hand[3][0] == hand[4][0] - 1
		&& hand[0][1] == hand[1][1] && hand[0][1] == hand[2][1] && hand[0][1] == hand[3][1] && hand[0][1] == hand[4][1];

}

bool CheckRoyalFlush(int hand[5][2]) {
	// pattern:
	// XXXXX
	// A-10-J-Q-K
	
	// if the first card isn't an ace and the second card isn't a 10, we don't have a royal flush (ace is 1, 10 is 10)
	//if (hand[0][0] != 1 || hand[1][0] != 10)
	//	return false;

	//int suit = hand[0][1];
	//int temp = 0;

	//// if every card doesn't have the same suit or doesn't increase from 1-13, we don't have a royal flush
	//for( int i = 0; i < 5; ++i )
	//{
	//	if( hand[i][0] <= temp || hand[i][1] != suit )
	//		return false;
	//	temp = hand[i][0];
	//}



	int suit = hand[0][1];

	// if every card doesn't have the same suit we don't have a flush
	for( int i = 0; i < 5; ++i )
	{
		if( hand[i][1] != suit )
			return false;
	}

	return hand[0][0] == 1 && hand[1][0] == 10 && hand[2][0] == 11 && hand[3][0] == 12 && hand[4][0] == 13;
}

bool CheckFlush(int hand[5][2]) {
	int suit = hand[0][1];

	// if every card doesn't have the same suit we don't have a flush
	for( int i = 0; i < 5; ++i )
	{
		if( hand[i][1] != suit )
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
		total ++;

		//put the array into a 2d array, making it easier to look at
		int newHand[5][2];
		for (int i = 0; i < 5; i++){
			newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
			newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
		}
		
		if(CheckRoyalFlush(newHand))
			frequencies["royalFlush"] += 1;
		else if(CheckStraightFlush(newHand))
			frequencies["straightFlush"] += 1;
		else if(CheckFourofKind(newHand))
			frequencies["fourOfAKind"] += 1;
		else if(CheckFullHouse(newHand))
			frequencies["fullHouse"] += 1;
		else if(CheckFlush(newHand))
			frequencies["flush"] += 1;
		else if(CheckStraight(newHand))
			frequencies["straight"] += 1;
		else if(CheckThreeofKind(newHand))
			frequencies["threeOfAKind"] += 1;
		else if(CheckTwoPair(newHand))
			frequencies["twoPair"] += 1;
		else if(CheckPair(newHand))
			frequencies["onePair"] += 1;
		else
			frequencies["noPair"] += 1;
/*
		typedef std::map<std::string, int>::iterator it_type;

		int foundCategories = 0;
		for(it_type iterator = frequencies.begin(); iterator != frequencies.end(); iterator++) {
			if( iterator->second != 0 )
				foundCategories ++;
			if( foundCategories == 9 )
				foundAll = true;
		}*/
		if (frequencies["royalFlush"] != 0)
			foundAll = true;
		
	}while (!foundAll);

	return frequencies;
}

int main(){
	map<string,int> frequencies = CheckFrequencies();

	//typedef std::map<std::string, int>::iterator it_type;
	//for(it_type iterator = frequencies.begin(); iterator != frequencies.end(); iterator++) {
	//	cout << iterator->first << ": " << iterator->second << endl;
	//}


	cout << setw(64) << right << "Poker Hand Frequency Simulation [SERIAL Version]" << endl;
	cout << setw(60) << right << "================================================================" << endl;
	cout << setw(16) << right << "Hand Type" << setw(18) << "Frequency" << setw(30) << "Relative Frequency (%)" << endl;
	cout << setw(60) << right << "----------------------------------------------------------------" << endl;
	cout << setw(16) << right << "No Pair" << setw(18) << frequencies["noPair"] << setw(30) << setprecision(6) << (frequencies["noPair"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "One Pair" << setw(18) << frequencies["onePair"] << setw(30) << setprecision(6) << (frequencies["onePair"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Two Pair" << setw(18) << frequencies["twoPair"] << setw(30) << setprecision(6) << (frequencies["twoPair"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Three of a Kind" << setw(18) << frequencies["threeOfAKind"] << setw(30) << setprecision(6) << (frequencies["threeOfAKind"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Straight" << setw(18) << frequencies["straight"] << setw(30) << setprecision(6) << (frequencies["straight"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Flush" << setw(18) << frequencies["flush"] << setw(30) << setprecision(6) << (frequencies["flush"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Full House" << setw(18) << frequencies["fullHouse"] << setw(30) << setprecision(6) << (frequencies["fullHouse"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Four of a Kind" << setw(18) << frequencies["fourOfAKind"] << setw(30) << setprecision(6) << (frequencies["fourOfAKind"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Straight Flush" << setw(18) << frequencies["straightFlush"] << setw(30) << setprecision(6) << (frequencies["straightFlush"] / (total * 1.0)) * 100 << endl;
	cout << setw(16) << right << "Royal Flush" << setw(18) << frequencies["royalFlush"] << setw(30) << setprecision(6) << (frequencies["royalFlush"] / (total * 1.0)) * 100 << endl;
	cout << setw(60) << right << "----------------------------------------------------------------" << endl;
	cout << setw(16) << right << "Hands Generated: " << setw(18) << total << endl;
	cout << setw(60) << right << "----------------------------------------------------------------" << endl;


	//Deck cards;
	//bool found = false;
	//do

	//{
	//	vector<int> hand = cards.getHand();
	//	//put the array into a 2d array, making it easier to look at
	//	int newHand[5][2];
	//	for (int i = 0; i < 5; i++){
	//		newHand[i][0] = atoi(to_string(hand[i]).substr(0, to_string(hand[i]).length() - 1).c_str());
	//		newHand[i][1] = atoi(to_string(hand[i]).substr(to_string(hand[i]).length() - 1, 1).c_str());
	//	}
	//	found = CheckPair(newHand);
	//} while(!found);

	//cout << "found pair" << endl;
	//




	/*vector<int> premade;
	premade.push_back(11);
	premade.push_back(101);
	premade.push_back(111);
	premade.push_back(121);
	premade.push_back(131);
	bool test = CheckRoyalFlush(premade);

	cout << test;*/
/*
	Deck cards;
	bool foundRF = false;
	do
	{
		vector<int> hand = cards.getHand();
		foundRF = CheckRoyalFlush(hand);
	} while(!foundRF);

	cout << "found Royal Flush" << endl;*/

	return 0;
}

