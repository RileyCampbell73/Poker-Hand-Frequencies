#include"Deck.h"

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

int main(){

	Deck cards;
	vector<int> hand = cards.getHand();

	return 0;
}

