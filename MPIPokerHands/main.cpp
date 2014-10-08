//	Pseudocode
//----------

//Master Process
//
//create map
//
//main loop while there are any slaves still "active"
//
//Create a hand and check it and store it
//check to see if all are found
//
//Checks for a message from any slave(NON - BLOCKING)
//if caught then terminate all slaves
//

//- Slave Processes
//
// create map
//
//loop
//
//Checks for a message from any slave(NON - BLOCKING)
//
//Create a hand and check it and store it
//check to see if all are found
//
//end loop



#include"Deck.h"

#include <map>
#include <iostream>
#include <iomanip>
#include <mpi.h>
using namespace std;

unsigned int total = 0;
const int TAG_DATA = 0, TAG_QUIT = 1, TAG_NEW_TYPE = 2, TAG_FOUND_ALL = 3;


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




void CheckFrequencies(map<string, int> &frequencies, Deck cards, int rank)
{
	vector<Card> hand = cards.getHand();
	MPI_Request request;
	static int msgBuff;

	if (CheckRoyalFlush(hand)){
		if (frequencies["royalFlush"] == 0 && rank > 0){
			msgBuff = 8;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["royalFlush"] += 1;
	}
	else if (CheckStraightFlush(hand)){
		if (frequencies["straightFlush"] == 0 && rank > 0){
			msgBuff = 7;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["straightFlush"] += 1;
	}
	else if (CheckFourofKind(hand)){
		if (frequencies["fourOfAKind"] == 0 && rank > 0){
			msgBuff = 6;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["fourOfAKind"] += 1;
	}
	else if (CheckFullHouse(hand))
	{
		if (frequencies["fullHouse"] == 0 && rank > 0){
			msgBuff = 5;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["fullHouse"] += 1;
	}
	else if (CheckFlush(hand)){
		if (frequencies["flush"] == 0 && rank > 0){
			msgBuff = 4;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["flush"] += 1;
	}
	else if (CheckStraight(hand)){
		if (frequencies["straight"] == 0 && rank > 0){
			msgBuff = 3;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["straight"] += 1;
	}
	else if (CheckThreeofKind(hand)){
		if (frequencies["threeOfAKind"] == 0 && rank > 0){
			msgBuff = 2;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["threeOfAKind"] += 1;
	}
	else if (CheckTwoPair(hand)){
		if (frequencies["twoPair"] == 0 && rank > 0){
			msgBuff = 1;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["twoPair"] += 1;
	}
	else if (CheckPair(hand)){
		if (frequencies["onePair"] == 0 && rank > 0){
			msgBuff = 0;
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_NEW_TYPE, MPI_COMM_WORLD, &request);
		}
		frequencies["onePair"] += 1;
	}
	else
		frequencies["noPair"] += 1;

}
bool FoundAll(map<string, int> &frequencies){
	return frequencies["noPair"] >= 1 && frequencies["onePair"] >= 1 && frequencies["twoPair"] >= 1 
		&& frequencies["threeOfAKind"] >= 1 && frequencies["straight"] >= 1 && frequencies["flush"] >= 1 
		&& frequencies["fullHouse"] >= 1 && frequencies["fourOfAKind"] >= 1 && frequencies["straightFlush"] >= 1
		&& frequencies["royalFlush"] >= 1;
}

void processMaster(int numProcs)
{
}
void processSlave(int rank)
{
	map<string, int> frequencies;
	int count = 0;
	static int msgBuff, recvFlag;
	MPI_Status status;
	MPI_Request request;
	Deck cards;

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
	bool foundMessageSent = false;
	bool foundAllHands = false;
	bool endProcess = false;

	do{
		MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &recvFlag, &status);
		
		if (recvFlag){
			MPI_Recv(&msgBuff, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (status.MPI_TAG == TAG_QUIT){
				endProcess = true;
			}
		}
		else if (!foundAllHands){
			count++;
			CheckFrequencies(frequencies, cards, rank);
			foundAllHands = FoundAll(frequencies);
		}
		else if (!foundMessageSent && foundAllHands){
			//send message that all were found
			MPI_Isend(&msgBuff, 1, MPI_INT, 0, TAG_FOUND_ALL, MPI_COMM_WORLD, &request);
			foundMessageSent = true;
		}
	} while (!endProcess);

	//send array of totals
	int totals[] = { frequencies["noPair"], frequencies["onePair"], frequencies["twoPair"], frequencies["threeOfAKind"], 
		frequencies["straight"], frequencies["flush"], frequencies["fullHouse"], frequencies["fourOfAKind"], 
		frequencies["straightFlush"], frequencies["royalFlush"], count };

	MPI_Send(totals, 11, MPI_INT, 0, TAG_DATA, MPI_COMM_WORLD);
}

int main(int argc, char* argv[]){


	//cout << setw(64) << right << "Poker Hand Frequency Simulation [SERIAL Version]" << endl;
	//cout << setw(60) << right << "================================================================" << endl;
	//cout << setw(16) << right << "Hand Type" << setw(18) << "Frequency" << setw(30) << "Relative Frequency (%)" << endl;
	//cout << setw(60) << right << "----------------------------------------------------------------" << endl;
	//cout << setw(16) << right << "No Pair" << setw(18) << frequencies["noPair"] << setw(30) << setprecision(6) << (frequencies["noPair"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "One Pair" << setw(18) << frequencies["onePair"] << setw(30) << setprecision(6) << (frequencies["onePair"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "Two Pair" << setw(18) << frequencies["twoPair"] << setw(30) << setprecision(6) << (frequencies["twoPair"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "Three of a Kind" << setw(18) << frequencies["threeOfAKind"] << setw(30) << setprecision(6) << (frequencies["threeOfAKind"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "Straight" << setw(18) << frequencies["straight"] << setw(30) << setprecision(6) << (frequencies["straight"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "Flush" << setw(18) << frequencies["flush"] << setw(30) << setprecision(6) << (frequencies["flush"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "Full House" << setw(18) << frequencies["fullHouse"] << setw(30) << setprecision(6) << (frequencies["fullHouse"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "Four of a Kind" << setw(18) << frequencies["fourOfAKind"] << setw(30) << setprecision(6) << (frequencies["fourOfAKind"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "Straight Flush" << setw(18) << frequencies["straightFlush"] << setw(30) << setprecision(6) << (frequencies["straightFlush"] / (count * 1.0)) * 100 << endl;
	//cout << setw(16) << right << "Royal Flush" << setw(18) << frequencies["royalFlush"] << setw(30) << setprecision(6) << (frequencies["royalFlush"] / (count * 1.0)) * 100 << endl;
	//cout << setw(60) << right << "----------------------------------------------------------------" << endl;
	//cout << setw(16) << right << "Hands Generated: " << setw(18) << count << endl;
	//cout << setw(60) << right << "----------------------------------------------------------------" << endl;

	if (MPI_Init(&argc, &argv) == MPI_SUCCESS)
	{
		// Obtain the rank and the # of processes
		int rank, numProcs;
		MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

		// Continue only if there is at least one slave process
		if (numProcs > 1)
		{
			MPI_Comm_rank(MPI_COMM_WORLD, &rank);

			if (rank == 0)
				processMaster(numProcs);
			else
				processSlave(rank);
		}
		else
		{
			cerr << "This program requires more than one process!" << endl;
		}

		MPI_Finalize();
	}

	return 0;
}

