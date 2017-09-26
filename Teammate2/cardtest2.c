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

int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed,
		   struct gameState *state);

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

// added my own game initialization to use with assignment 3
int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed,
		   struct gameState *state) {

  int i;
  int j;
  int it;			
  //set up random number generator
  SelectStream(1);
  PutSeed((long)randomSeed);
  
  //check number of players
  if (numPlayers > MAX_PLAYERS || numPlayers < 2)
    {
      return -1;
    }

  //set number of players
  state->numPlayers = numPlayers;

  //check selected kingdom cards are different
  for (i = 0; i < 10; i++)
    {
      for (j = 0; j < 10; j++)
        {
	  if (j != i && kingdomCards[j] == kingdomCards[i])
	    {
	      return -1;
	    }
        }
    }


  //initialize supply
  ///////////////////////////////

  //set number of Curse cards
  if (numPlayers == 2)
    {
      state->supplyCount[curse] = 10;
    }
  else if (numPlayers == 3)
    {
      state->supplyCount[curse] = 20;
    }
  else
    {
      state->supplyCount[curse] = 30;
    }

  //set number of Victory cards
  if (numPlayers == 2)
    {
      state->supplyCount[estate] = 8;
      state->supplyCount[duchy] = 8;
      state->supplyCount[province] = 8;
    }
  else
    {
      state->supplyCount[estate] = 12;
      state->supplyCount[duchy] = 12;
      state->supplyCount[province] = 12;
    }

  //set number of Treasure cards
  state->supplyCount[copper] = 60 - (7 * numPlayers);
  state->supplyCount[silver] = 40;
  state->supplyCount[gold] = 30;

  //set number of Kingdom cards
  for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
      for (j = 0; j < 10; j++)           		//loop chosen cards
	{
	  if (kingdomCards[j] == i)
	    {
	      //check if card is a 'Victory' Kingdom card
	      if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
		{
		  if (numPlayers == 2){ 
		    state->supplyCount[i] = 8; 
		  }
		  else{ state->supplyCount[i] = 12; }
		}
	      else
		{
		  state->supplyCount[i] = 10;
		}
	      break;
	    }
	  else    //card is not in the set choosen for the game
	    {
	      state->supplyCount[i] = -1;
	    }
	}

    }

  ////////////////////////
  //supply intilization complete

  //set player decks
  // start all players with empty decks for the test games
 
  for (i = 0; i < numPlayers; i++)
    {
      state->deckCount[i] = 0;
      for (j = 0; j < 3; j++)
	{
	  state->deck[i][j] = estate;
	  state->deckCount[i]++;
	}
      for (j = 3; j < 10; j++)
	{
	  state->deck[i][j] = copper;
	  state->deckCount[i]++;		
	}
    }

  //shuffle player decks
  for (i = 0; i < numPlayers; i++)
    {
      if ( shuffle(i, state) < 0 )
	{
	  return -1;
	}
    }

  // set counts to 0
  for (i = 0; i < numPlayers; i++)
    {  
      //initialize hand size to zero
      state->handCount[i] = 0;
      state->discardCount[i] = 0;
    }
  
  //set embargo tokens to 0 for all supply piles
  for (i = 0; i <= treasure_map; i++)
    {
      state->embargoTokens[i] = 0;
    }

  //initialize first player's turn
  state->outpostPlayed = 0;
  state->phase = 0;
  state->numActions = 1;
  state->numBuys = 1;
  state->playedCardCount = 0;
  state->whoseTurn = 0;
  state->handCount[state->whoseTurn] = 0;
  //int it; move to top

  //Moved draw cards to here, only drawing at the start of a turn
  //for (it = 0; it < 5; it++){
  //  drawCard(state->whoseTurn, state);
  //}

  updateCoins(state->whoseTurn, state, 0);

  return 0;
}
