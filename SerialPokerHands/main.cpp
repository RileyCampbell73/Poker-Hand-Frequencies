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

int main(){

	Deck cards;

	vector<int> hand = cards.getHand();

	bool check = CheckPair(hand);

	//this whole thing could have been done better.
	
	return 0;
}

