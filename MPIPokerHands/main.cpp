/*
	Authors: Riley Campbell, James Haig
	Purpose: Computes the frequencies of all 10 different types of poker hands using MPI to facilitate message passing.
	Date: October 9, 2014
*/

#include "Utilities.h"

#include <map>
#include <iostream>
#include <iomanip>
#include <mpi.h>
using namespace std;

unsigned int total = 0;
const int TAG_DATA = 0, TAG_QUIT = 1, TAG_NEW_TYPE = 2;

// Draws a hand, checks its type, and records what type of hand was found.
// If a slave runs this method, it will also send a message to the master if the hand found is a type that slave has never found before
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

// Checks whether or not we've found all the different types of hands at least once
bool FoundAll(map<string, int> &frequencies){
	return frequencies["royalFlush"] >= 1 && frequencies["straightFlush"] >= 1 && frequencies["fourOfAKind"] >= 1
		&& frequencies["fullHouse"] >= 1 && frequencies["flush"] >= 1 && frequencies["straight"] >= 1
		&& frequencies["threeOfAKind"] >= 1 && frequencies["twoPair"] >= 1 && frequencies["onePair"] >= 1
		&& frequencies["noPair"] >= 1;
}

// Sends a terminate message to all slave processes
bool terminateSlaves(int numProcs)
{
    int msgBuff = 0;

    for(int p = 1; p < numProcs; ++p)
        MPI_Send(&msgBuff, 1, MPI_INT, p, TAG_QUIT, MPI_COMM_WORLD);

	return true;
}

// Combines a slave's results (passed as an array) to the master's frequencies
void calculateSlaveResults(int &count, map<string, int> &frequencies, int results[11])
{
	// combine the results
	frequencies["noPair"] += results[0];
	frequencies["onePair"] += results[1];
	frequencies["twoPair"] += results[2];
	frequencies["threeOfAKind"] += results[3];
	frequencies["straight"] += results[4];
	frequencies["flush"] += results[5];
	frequencies["fullHouse"] += results[6];
	frequencies["fourOfAKind"] += results[7];
	frequencies["straightFlush"] += results[8];
	frequencies["royalFlush"] += results[9];
	count += results[10];
	
}

// Checks if all of the types of hands have been found in the slaves
bool checkAllTypes (bool (&typesOfHands)[9])
{
	for( int i = 0; i < 9; ++i )
	{
		if( typesOfHands[i] == false )
			return false;
	}
	return true;
}

// Master process calls this method to check if there is a new type of hand found in any of the slaves
bool checkMessagesFromSlaves( map<string, int> &frequencies, bool (&typesOfHands)[9] )
{
    static int msgBuff, recvFlag;
    MPI_Status status;
    static MPI_Request request;
	bool slavesTerminated = false;
	MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &recvFlag, &status);
	do{
		// Test to see if a message has "come in"
		if (recvFlag)
		{
			// Message is waiting to be received
			MPI_Recv(&msgBuff, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

			if (status.MPI_TAG == TAG_NEW_TYPE)
			{
				// we have a new type of hand
				// 0 = "one pair", 8 = "royal flush"
				typesOfHands[msgBuff] = true;

				// Reset the Request handle
				request = 0;
			}
		}
		MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &recvFlag, &status);
	}while (recvFlag);
	return checkAllTypes(typesOfHands);
}

// Output the report
void report (int count, map<string, int> frequencies, double time, int numProcs)
{	
	cout << setw(64) << right << "Poker Hand Frequency Simulation [PARALLEL Version]" << endl;
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
	cout << setw(14) << right << "Elapsed Time (s): " << setw(16) << time << endl;
	cout << setw(16) << right << "Number of Processes: " << setw(13) << numProcs << endl;
	cout << setw(60) << right << "----------------------------------------------------------------" << endl;
}

// Master process records our time, checks for messages from the slaves, and processes hands if all of the different types of hands haven't been found
// Once all types have been found, master process sends a terminate message to the slaves, and waits for their individual results
void processMaster(int numProcs)
{
	Deck cards;
	
	int masterCount = 0;
	map<string, int> masterFrequencies;
	masterFrequencies["noPair"] = 0;
	masterFrequencies["onePair"] = 0;
	masterFrequencies["twoPair"] = 0;
	masterFrequencies["threeOfAKind"] = 0;
	masterFrequencies["straight"] = 0;
	masterFrequencies["flush"] = 0;
	masterFrequencies["fullHouse"] = 0;
	masterFrequencies["fourOfAKind"] = 0;
	masterFrequencies["straightFlush"] = 0;
	masterFrequencies["royalFlush"] = 0;


	// structure to check that we have at least one of each type (not checking for "no pair")
	bool typesOfHands[9] = {false}; // all initialized to false

	bool haveAllTypes = false; // set to false when either the master or one of the slaves have found all of the types of hands

	double startTime = MPI_Wtime();

	do
	{
		// check for messages from the slaves
		haveAllTypes = checkMessagesFromSlaves(masterFrequencies, typesOfHands);

		if(!haveAllTypes)
		{
			// do roughly the same operations as the slaves, get hand, check hand, calc frequencies
			masterCount++;
			CheckFrequencies(masterFrequencies, cards, 0);
			haveAllTypes = FoundAll(masterFrequencies);

		}
		
	} while(!haveAllTypes);

	// send shut down message since we have all the types of hands at this point
	terminateSlaves(numProcs);

	// once we send the terminate messages, check for the results messages
	for( int i = 1; i <= numProcs - 1; ++ i )
	{
		int results[11];

		MPI_Status status;
		MPI_Recv(results, 11, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			calculateSlaveResults(masterCount, masterFrequencies, results);
	}

	double elapsedTime = MPI_Wtime() - startTime;

	// report the results
	report(masterCount, masterFrequencies, elapsedTime, numProcs);
}

// Slaves check for terminate messages from the master process, and draw hands to record their frequencies
// Once a terminate message is received the slave will send back a message with all of their results
void processSlave(int rank)
{
	
	map<string, int> frequencies;
	int count = 0;
	static int msgBuff = 0, recvFlag;
	MPI_Status status;
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

	bool foundMessageSent = false;
	bool foundAllHands = false;
	bool endProcess = false;

	do{
		MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &recvFlag, &status);
		
		if (recvFlag){
			MPI_Recv(&msgBuff, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (status.MPI_TAG == TAG_QUIT){
				endProcess = true;
			}
		}
		else if (!endProcess){
			count++;
			CheckFrequencies(frequencies, cards, rank);
		}


	} while (!endProcess);

	//send array of totals
	int totals[] = { frequencies["noPair"], frequencies["onePair"], frequencies["twoPair"], frequencies["threeOfAKind"], 
		frequencies["straight"], frequencies["flush"], frequencies["fullHouse"], frequencies["fourOfAKind"], 
		frequencies["straightFlush"], frequencies["royalFlush"], count };

	MPI_Send(totals, 11, MPI_INT, 0, TAG_DATA, MPI_COMM_WORLD);
}

// Display a brief message
void welcomeMessage()
{
	cout << "Welcome to the poker hand frequencies simulation!  This program will draw random 5 card hands from a simulated deck of cards. This is the parallel version and will use MPI to facilitate message passing between processes.  Uses however many processes you specify with an mpiexec call.  \nAuthors: Riley Campbell, James Haig. " << endl;
}

int main(int argc, char* argv[]){

	welcomeMessage();
	if (MPI_Init(&argc, &argv) == MPI_SUCCESS)
	{
		// Obtain the rank and the # of processes
		int rank, numProcs;
		MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		srand((rank + 1) * time(0));
		
		if (rank == 0)
			processMaster(numProcs);
		else
			processSlave(rank);

		MPI_Finalize();
	}
	
	return 0;
}

