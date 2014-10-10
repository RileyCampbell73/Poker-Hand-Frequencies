/*
	Authors: Riley Campbell, James Haig
	Purpose: Computes the frequencies of all 10 different types of poker hands.  Serial version
	Date: October 9, 2014
*/

#include "Utilities.h"

#include <map>
#include <iostream>
#include <iomanip>
#include <mpi.h>
using namespace std;

unsigned int total = 0;

map<string, int> frequencies;

// Checks whether or not we've found all the different types of hands at least once
bool FoundAll(map<string, int> &frequencies){
	return frequencies["royalFlush"] >= 1 && frequencies["straightFlush"] >= 1 && frequencies["fourOfAKind"] >= 1
		&& frequencies["fullHouse"] >= 1 && frequencies["flush"] >= 1 && frequencies["straight"] >= 1
		&& frequencies["threeOfAKind"] >= 1 && frequencies["twoPair"] >= 1 && frequencies["onePair"] >= 1
		&& frequencies["noPair"] >= 1;
}

// Draws a hand and checks its type, and records its findings in the global frequencies map
void CheckFrequencies(Deck cards)
{
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
}

// Output
void report (int count, double time)
{
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
	cout << setw(16) << right << "Hands Generated: " << setw(17) << count << endl;
	cout << setw(16) << right << "Elapsed Time: " << setw(17) << time << endl;
	cout << setw(60) << right << "----------------------------------------------------------------" << endl;
}

// Display a brief message
void welcomeMessage()
{
	cout << "Welcome to the poker hand frequencies simulation!  This program will draw random 5 card hands from a simulated deck of cards. This is the serial version and will only use one process.  \nAuthors: Riley Campbell, James Haig. " << endl;
}

int main(int argc, char* argv[]){
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

	Deck cards;
	//start time
	double startTime = MPI_Wtime();
	welcomeMessage();
	do{
		count++;
		CheckFrequencies(cards);
	} while (!FoundAll(frequencies));
	double elapsedTime = MPI_Wtime() - startTime;

	report (count, elapsedTime);

	return 0;
}

