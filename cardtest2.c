/*
 * 
 * adventurer - make sure deck doesn't need to be shuffled
 *		see if card drawn is treasure card, 
 *		increment until 2 treasure cards or deck is empty
 *		discard all drawn cards that aren't treasure cards
 *	- stops when 2 treasure cards are revealed
 * 	- all revealed non-treasure cards are discarded
 *	- no treasure cards in deck (end of deck)
 *	- deck is shuffled when needed (at beginning and middle) **
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#define TESTCARD "adventurer"

int main() {

    int i;
    int handPos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    int numBefore;
    int numAfter;
    int coinsBefore;
    int coinsAfter;
    int deckCount = 0;
    int card = 0;
    int bonus = 0;

	struct gameState G, testG, oldG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, gardens, smithy, council_room};

	// initialize a game state and player cards
	initTestGame(numPlayers, k, seed, &G);


	printf("\n\n\n\n---------------- cardtest2 ----------------\n\n");

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	/*************** TEST 1: Two treasure cards are revealed ***********/
	printf("*******TEST 1: Two treasure cards are revealed *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// make sure the player has treasure cards
	gainCard(copper,&testG,1,player);
	gainCard(silver,&testG,1,player);
	gainCard(gold,&testG,1,player);

	// record coin amount before card is played
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
        	gainCard(gardens,&testG,1,player);
      	}

	// give player an adventurer card and play it
	gainCard(adventurer,&testG,2,player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);


	// this will fail due to the altered dominion.c code
	if(coinsAfter == 5)
	{
		printf("PASS: Two treasure cards are revealed\n\n\n");
		
	}
	else
	{	printf("FAIL: Two treasure cards are revealed\n\n\n"); }




	/*************** TEST 2: No treasure cards in deck ***********/
	printf("*******TEST 2: No treasure cards in deck *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// record coin amount before card is played
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
        	gainCard(gardens,&testG,1,player);
      	}

	// give player an adventurer card and play it
	gainCard(adventurer,&testG,2,player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);

	// test passes if player gains no coins from playing the adventurer card	
	if(coinsAfter == 0)
	{
		printf("PASS: No treasure cards in deck\n\n\n");
		
	}
	else
	{	printf("FAIL: No treasure cards in deck\n\n\n"); }



	/*************** TEST 3: One treasure card in deck ***********/
	printf("*******TEST 3: One treasure card in deck *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// record coin amount before card is played
	gainCard(silver,&testG,1,player);
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
        	gainCard(gardens,&testG,1,player);
      	}

	// give player an adventurer card and play it
	gainCard(adventurer,&testG,2,player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);

	// test passes if player gains no coins from playing the adventurer card
	if(coinsAfter == 0)
	{
		printf("PASS: One treasure card in deck\n\n\n");
		
	}
	else
	{	printf("FAIL: One treasure card in deck\n\n\n"); }



	
	/*************** TEST 4: All revealed non-treasure cards are discarded ***********/
	printf("*******TEST 4: All revealed non-treasure cards are discarded *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player treasure cards and record card amounts before card is played
	gainCard(silver,&testG,1,player);
	gainCard(silver,&testG,1,player);
	gainCard(silver,&testG,1,player);
	numBefore = numHandCards(&testG);

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
        	gainCard(gardens,&testG,1,player);
      	}

	// give player an adventurer card and play it
	gainCard(adventurer,&testG,2,player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get card amounts after card is played
	oldG = testG;	
	endTurn(&testG);
	numAfter = numHandCards(&oldG);


	// test passes if player's hand cointains only the adventurer card 
	if(numAfter == (numBefore + 1))
	{
		printf("PASS: All revealed non-treasure cards are discarded\n\n\n");
		
	}
	else
	{	printf("FAIL: All revealed non-treasure cards are discarded\n\n\n"); }

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}

