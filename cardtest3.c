/*
 * 
 * village - 	receives 1 card
 *		gain 2 actions
 *		discard card in hand
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


#define TESTCARD "village"

int main() {
    int handPos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    int numBefore;
    int numAfter;
    int numActBefore;
    int numActAfter;
    int card = 2;
    int bonus = 0;
    
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initTestGame(numPlayers, k, seed, &G);

	printf("\n\n\n\n---------------- cardtest3 ----------------\n\n");


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	/*************** TEST 1: User gets +1 card ***********/
	printf("*******TEST 1: User gets +1 card *******\n");

	// copy the game state to a test case and assign player to variable
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give the player a village card
	assert(numHandCards(&testG) == 0);
	assert(gainCard(village,&testG,2,player) == 0);
	assert(numHandCards(&testG) == 1);

	// record number of cards in hand before and after the card is played
	numBefore = numHandCards(&testG);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);
	numAfter = numHandCards(&testG);

	// end current turn
	endTurn(&testG);

	// test passes if number of cards in hand is one more than start, minus one discarded
	if(numAfter == (numBefore + 1 - 1))
	{
		printf("PASS: User gets +1 card\n\n\n");
		
	}


	else
	{	printf("FAIL: User gets +1 card\n\n\n"); }




	/*************** TEST 2: User discards card in hand ***********/
	printf("*******TEST 2: User discards card in hand *******\n");

	// copy the game state to a test case and assign player to variable
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give the player a village card
	assert(numHandCards(&testG) == 0);
	assert(gainCard(village,&testG,2,player) == 0);
	assert(numHandCards(&testG) == 1);

	// record number of cards in hand before and after the card is played
	numBefore = numHandCards(&testG);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);
	numAfter = numHandCards(&testG);

	// end current turn
	endTurn(&testG);

	// test passes if number of cards in hand is one more than start, minus one discarded
	if(numAfter == (numBefore + 1 - 1))
	{
		printf("PASS: User discards card in hand\n\n\n");
		
	}

	
	else
	{	printf("FAIL: User discards card in hand\n\n\n"); }





	/*************** TEST 3: User gains two actions ***********/
	printf("*******TEST 3: User gains two actions *******\n");

	// copy the game state to a test case and assign player to variable
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;	

	// give the player a village card
	assert(numHandCards(&testG) == 0);
	assert(gainCard(village,&testG,2,player) == 0);
	assert(numHandCards(&testG) == 1);

	// record number of actions before and after the card is played
	numActBefore = testG.numActions;
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);
	numActAfter = testG.numActions;

	// end current turn
	endTurn(&testG);


	// this will fail due to the altered code in dominion.c
	if(numActAfter == (numActBefore + 2 - 1))
	{
		printf("PASS: User gains two actions\n\n\n");
		
	}
	else
	{	printf("FAIL: User gains two actions\n\n\n"); }


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}

