/*

updateCoins - 	reset coin count
		add coins for each treasure card in player's hand
		add bonus



- Play no treasure cards
- Play copper
- Play silver
- Play gold
- Play multiple
- Play bonus

*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>


int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed,
		   struct gameState *state);

int main (int argc, char** argv) {
  struct gameState state;
  struct gameState previousState;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, council_room, smithy};

  int seed = 2;
  


  int player = 0;
  int bonus = 0;


	printf("\n\n\n\n---------------- unittest1 ----------------\n\n");
	printf("----------------Testing Card: updateCoins----------------\n");

	/******* Test no treasure cards with other cards in hand *******/

	printf("*******Test1: No Treasure Cards*******\n");
	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(council_room,&state,2,player) == 0);
	assert(numHandCards(&state) == 1);
	previousState = state;
	updateCoins(player, &state, bonus);
	if(state.coins == 0)
	{
		printf("PASS: No treasue cards\n\n\n");
		
	}
	else
	{	printf("FAIL: No treasue cards\n\n\n"); }






	/******* Test single copper with no other cards *******/

	printf("*******Test2: Play Single Copper*******\n");
	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(copper,&state,2,player) == 0);
	assert(numHandCards(&state) == 1);
	previousState = state;
	updateCoins(player, &state, bonus);
	if(state.coins == 1)
	{
		printf("PASS: playing single copper coin\n\n\n");
		
	}
	else
	{	printf("FAIL: playing single copper coin\n\n\n"); }




	/******* Test single silver with no other cards *******/

	printf("*******Test3: Play Single Silver*******\n");
	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(silver,&state,2,player) == 0);
	assert(numHandCards(&state) == 1);
	previousState = state;
	updateCoins(player, &state, bonus);
	if(state.coins == 2)
	{
		printf("PASS: playing single silver coin\n\n\n");
		
	}
	else
	{	printf("FAIL: playing single silver coin\n\n\n"); }




	/******* Test single gold with no other cards *******/

	printf("*******Test4: Play Single Gold*******\n");
	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(gold,&state,2,player) == 0);
	assert(numHandCards(&state) == 1);
	previousState = state;
	updateCoins(player, &state, bonus);
	if(state.coins == 3)
	{
		printf("PASS: playing single gold coin\n\n\n");
		
	}
	else
	{	printf("FAIL: playing single gold coin\n\n\n"); }




	/******* Test one copper, one silver, one gold *******/

	printf("*******Test5: Play one copper, one silver, one gold*******\n");
	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(copper,&state,2,player) == 0);
	assert(gainCard(silver,&state,2,player) == 0);
	assert(gainCard(gold,&state,2,player) == 0);
	assert(numHandCards(&state) == 3);
	previousState = state;
	updateCoins(player, &state, bonus);
	if(state.coins == 6)
	{
		printf("PASS: playing one copper, one silver, one gold\n\n\n");
		
	}
	else
	{	printf("FAIL: playing one copper, one silver, one gold\n\n\n"); }





	/******* Test two copper with bonus of 6 *******/

	printf("*******Test6: Play Two Copper with Bonus of 6*******\n");
	initTestGame(3, k, seed, &state);
	bonus = 6;
	assert(numHandCards(&state) == 0);
	assert(gainCard(copper,&state,2,player) == 0);
	assert(gainCard(copper,&state,2,player) == 0);
	assert(numHandCards(&state) == 2);
	previousState = state;
	updateCoins(player, &state, bonus);
	if(state.coins == 8)
	{
		printf("PASS: playing two copper with bonus of 6\n\n\n");
		
	}
	else
	{	printf("FAIL: playing two copper with bonus of 6\n\n\n"); }




	printf("*******Testing updateCoins Complete!*******\n\n\n");
	return 0;
} // main


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




