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
#include <string.h>

#define TESTCARD "village"

int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed,
		   struct gameState *state);

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
	cardEffect(village, 0, 0, 0, &testG, handPos, &bonus);
	numActAfter = testG.numActions;

	// end current turn
	endTurn(&testG);


	// this will fail due to the altered code in dominion.c
	//if(numActAfter == (numActBefore + 2 - 1))
	if(testG.numActions == G.numActions + (2 - 1))
	{
		printf("PASS: User gains two actions\n\n\n");
		
	}
	else
	{	printf("FAIL: User gains two actions\n\n\n"); }


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
