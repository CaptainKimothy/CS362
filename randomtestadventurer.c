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

gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>


int chechAdventurer(int numPlayers, struct gameState *G, *results);




/*
	for(i = 0; i < 1000; i++) // fuzzing
	{
		seed = time(NULL);
		numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
		player = rand() % numPlayers;

		// initialize a new game state
		G = randomTestGame(numPlayers, seed);

		deckCount = 10;

		// fill players deck with gardens cards
		for (i = 0; i < deckCount; i++)
		{
        		if (j > sizeDeck / 2 && treasure < 2)
			{
				g->deck[player][j] = rand() % 3 + copper;
				treasure++;
			} else
			{
				g->deck[player][j] = rand() % ( treasure_map + 1 );
				if (g->deck[player][j] == copper || g->deck[player][j] == silver
						|| g->hand[player][j] == gold)
				{
					treasure++;
				}
			}
      		}

*/		


int main() {

/*
    int i;
    int handPos = 0;
    
    int numPlayers;
    int player = 0;
    int numBefore;
    int numAfter;
    int coinsBefore;
    int coinsAfter;
    int deckCount = 0;
    int numPassed = 0;
    int numFailed = 0;
*/

  int i, n, r, p, m, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int results[4] = {0, 0, 0, 0};

  struct gameState G;

  printf ("Testing drawCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.numPlayers = floor(Random() * MAX_PLAYERS);
    int player = floor(Random() * MAX_PLAYERS);
    G.hand[player][G.handCount[player]]=floor(Random() * MAX_HAND);
    checkAdventurer(player, &G, &results);
  }

  printf("Random adventurer card testing results:\n\n");
  printf("Player gains two treasure cards: Failed: %d\n", results[0]);
  printf("No treasure cards in deck: Failed: %d\n", results[1]);
  printf("One treasure card in deck: Failed: %d\n", results[2]);
  printf("All revealed non-treasure cards discarded: Failed: %d\n\n", results[3]);

   return 0;
} // main



void checkAdventurer(int player, struct gameState *G, *results)
{
	srand(time(NULL));
	struct gameState testG;
	memcpy(&testG, G, sizeof(struct gameState));
	//int error1 = 0, error2 = 0, error3 = 0, error4 = 0;



	/*************** TEST 1: Player gains two treasure cards ***********/
	// copy the game state to a test case
	memcpy(&testG, G, sizeof(struct gameState));
	//player = testG.whoseTurn;

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

	testG = G;

	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);


	// this will fail due to the altered dominion.c code
	if(testG.coins == G.coins + 5) //(coinsAfter != 5)
	{
		results[0]++;	
	}



	/*************** TEST 2: No treasure cards in deck ***********/
	//printf("*******TEST 2: No treasure cards in deck *******\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//player = testG.whoseTurn;

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

	testG = G;

	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);

	// test passes if player gains no coins from playing the adventurer card	
	if(testG.coins == G.coins) //(coinsAfter != 0)
	{
		results[1]++;	
	}




	/*************** TEST 3: One treasure card in deck ***********/
	//printf("*******TEST 3: One treasure card in deck *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//player = testG.whoseTurn;

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

	testG = G;
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);

	// test passes if player gains no coins from playing the adventurer card
	if(testG.coins > G.coins) //(coinsAfter != 0)
	{
		results[2]++;	
	}



	
	/*************** TEST 4: All revealed non-treasure cards are discarded ***********/
	//printf("*******TEST 4: All revealed non-treasure cards are discarded *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//player = testG.whoseTurn;

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

	testG = G;

	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get card amounts after card is played
	//oldG = testG;	
	endTurn(&testG);
	numAfter = numHandCards(&oldG);


	// test passes if player's hand cointains only the adventurer card 
	if(numHandCards(&testG) != numHandCards(&G) + 1) //numAfter != (numBefore + 1))
	{
		results[3]++;	
	}


	printf("\n >>>>> SUCCESS: Random Testing Complete for %s <<<<<\n\n", TESTCARD);


	//return 0;
}

