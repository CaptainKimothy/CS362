/* Author: Kim McLeod
 * Assignment: 4
 * File: randomtestcard.c
 *
 *
 * smithy - 	receives three cards
 *		discards card in hand
 *
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#define TESTCARD "smithy"

int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed,
		   struct gameState *state);

int main() {

    int i, error1 = 0, error2 = 0;
    int handpos = 0;    
    int seed = 2000;
    int player = 0;
    int numBefore;
    int numAfter;
    int bonus = 0;
    int card = 0;
    int numPlayers;

	struct gameState G, testG;
	int k[10] = {smithy, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, adventurer, council_room};

	printf("---------------- Random Testing for %s Begin ----------------\n", TESTCARD);
for(i = 0; i < seed; i++){
	player = floor(Random() * 2);
	numPlayers = floor(Random() * MAX_PLAYERS);
	G.deckCount[player] = floor(Random() * MAX_DECK);
	G.discardCount[player] = floor(Random() * MAX_DECK);
	G.handCount[player] = floor(Random() * MAX_HAND);


	// initialize a game state and player cards
	initTestGame(numPlayers, k, seed, &G);


	

	/*************** TEST 1: User gets +3 cards ***********/
	


	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player smithy card
	gainCard(smithy,&testG,2,player);


	// record number of cards before and after smithy is played
	numBefore = numHandCards(&testG);
	cardEffect(card, 0, 0, 0, &testG, handpos, &bonus);
	numAfter = numHandCards(&testG);


	endTurn(&testG);


	// test passes if number of cards in hand is 3 more
	// than start, minus one discarded
	// this will fail due to alterations in the dominion.c code
	if(numAfter != (numBefore + 3 - 1))
	{	printf("Error 1 'User gains 3 cards' Expected: %d, Actual %d\n", (numBefore + 3 - 1), numAfter);
		error1++;
		
	}





	/*************** TEST 2: User discards card in hand ***********/
	

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player smithy card
	gainCard(smithy,&testG,2,player);


	// record number of cards before and after smithy is played
	numBefore = numHandCards(&testG);
	cardEffect(card, 0, 0, 0, &testG, handpos, &bonus);
	numAfter = numHandCards(&testG);

	endTurn(&testG);

	// test passes if number of cards in hand is 3 more
	// than start, minus one discarded
	// this will fail due to alterations in the dominion.c code
	if(&testG.discardCount[player] != &G.discardCount[player])
	{	printf("Error 2 'User discards smithy card' Expected: %d, Actual: %d\n", &G.discardCount[player], &testG.discardCount[player]);
		error2++;
		
	}



    }


	printf("\n >>>>> SUCCESS: Testing complete for %s <<<<<\n\n", TESTCARD);
    

	printf("Error 1 'User gains 3 cards' Failed %d of %d times\n", error1, seed); 
	printf("Error 2 'User discards smithy card' Failed %d of %d times\n\n\n\n", error2, seed);

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

