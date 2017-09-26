/*
 * 
 * great_hall - 	gain 1 card
 *			gain 1 action
 *			discard card in hand
 *
 *
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#define TESTCARD "great_hall"

int main() {


    int handPos = 0;

    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    int numBefore;
    int numAfter;
    int numActBefore;
    int numActAfter;

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};

	// initialize a game state and player cards
	initTestGame(numPlayers, k, seed, &G);

	printf("\n\n\n\n---------------- cardtest4 ----------------\n\n");


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	/*************** TEST 1: User gets +1 card ***********/
	printf("*******TEST 1: User gets +1 card *******\n");

	// copy the game state to a test case and assign current player to variable
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give the player a great_hall card
	assert(numHandCards(&testG) == 0);
	assert(gainCard(great_hall,&testG,2,player) == 0);
	assert(numHandCards(&testG) == 1);

	// find number of cards before and after card is played
	numBefore = numHandCards(&testG);
	playCard(handPos, 0, 0, 0, &testG);
	numAfter = numHandCards(&testG);

	// end current turn
	endTurn(&testG);

	// if player has one more card than they started, minus the discarded card,
	// the test passes
	if(numAfter == (numBefore + 1 - 1))
	{
		printf("PASS: User gets +1 card\n\n\n");
		
	}
	// otherwise it fails
	else
	{	printf("FAIL: User gets +1 card\n\n\n"); }




	/*************** TEST 2: User discards card in hand ***********/
	printf("*******TEST 2: User discards card in hand *******\n");

	// copy the game state to a test case and assign current player to variable
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give the player a great_hall card
	assert(numHandCards(&testG) == 0);
	assert(gainCard(great_hall,&testG,2,player) == 0);
	assert(numHandCards(&testG) == 1);

	// find number of cards before and after card is played
	numBefore = numHandCards(&testG);
	playCard(handPos, 0, 0, 0, &testG);
	numAfter = numHandCards(&testG);

	// end current turn
	endTurn(&testG);

	// if player has one more card than they started, minus the discarded card,
	// the test passes
	if(numAfter == (numBefore + 1 - 1))
	{
		printf("PASS: User discards card in hand\n\n\n");
		
	}

	// otherwise it fails
	else
	{	printf("FAIL: User discards card in hand\n\n\n"); }



	/*************** TEST 3: User gains one action ***********/
	printf("*******TEST 3: User gains one action *******\n");

	// copy the game state to a test case and assign current player to variable
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;	

	// give the player a great_hall card
	assert(numHandCards(&testG) == 0);
	assert(gainCard(great_hall,&testG,2,player) == 0);
	assert(numHandCards(&testG) == 1);

	// find number of actions before and after card is played
	numActBefore = testG.numActions;
	playCard(handPos, 0, 0, 0, &testG);
	numActAfter = testG.numActions;

	// end current turn
	endTurn(&testG);

	// if player has one more action than they started, minus the discarded card,
	// the test passes
	if(numActAfter == (numActBefore + 1 - 1))
	{
		printf("PASS: User gains one action\n\n\n");
		
	}

	// otherwise the test fails
	else
	{	printf("FAIL: User gains one action\n\n\n"); }


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


