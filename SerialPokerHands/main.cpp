#include"Deck.h"

#include <iostream>
using namespace std;

void HandParser(vector<Card> hand){

}

int main(){

	Deck cards;

	//cout << cards.deck[1].suit << endl;
	//for (;;){
		vector<Card> hand = cards.getHand();
		
		HandParser(hand);
	//}
	return 0;
}
