/*
 * 
 * smithy - 	receives three cards
 *		discards card in hand
 *
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#define TESTCARD "smithy"

int main() {
    int discarded = 1;
    int handpos = 0;    
    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    int numBefore;
    int numAfter;
    int bonus = 0;
    int card = 8;

	struct gameState G, testG, oldG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initTestGame(numPlayers, k, seed, &G);


	printf("\n\n\n\n---------------- cardtest1 ----------------\n\n");

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	/*************** TEST 1: User gets +3 cards ***********/
	printf("*******TEST 1: User gets +3 cards *******\n");


	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player smithy card
	assert(numHandCards(&testG) == 0);
	assert(gainCard(smithy,&testG,2,player) == 0);
	assert(numHandCards(&testG) == 1);

	// record number of cards before and after smithy is played
	numBefore = numHandCards(&testG);
	cardEffect(card, 0, 0, 0, &testG, handpos, &bonus);
	numAfter = numHandCards(&testG);


	endTurn(&testG);


	// test passes if number of cards in hand is 3 more
	// then start, minus one discarded
	// this will fail due to alterations in the dominion.c code
	if(numAfter == (numBefore + 3 - 1))
	{
		printf("PASS: User gets +3 cards\n\n\n");
		
	}
	else
	{	printf("FAIL: User gets +3 cards\n\n\n"); }




	/*************** TEST 1: User discards card in hand ***********/
	printf("*******TEST 2: User discards card in hand *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player smithy card

	assert(numHandCards(&testG) == 0);
	assert(gainCard(smithy,&testG,2,player) == 0);
	assert(numHandCards(&testG) == 1);

	// record number of cards before and after smithy is played
	numBefore = numHandCards(&testG);
	cardEffect(card, 0, 0, 0, &testG, handpos, &bonus);
	numAfter = numHandCards(&testG);

	endTurn(&testG);

	// test passes if number of cards in hand is 3 more
	// then start, minus one discarded
	// this will fail due to alterations in the dominion.c code
	if(numAfter == (numBefore + 3 - 1))
	{
		printf("PASS: User discards card in hand\n\n\n");
		
	}
	else
	{	printf("FAIL: User discards card in hand\n\n\n"); }


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}

