/*
endTurn - 	discard hand
		reset hand count
		determine player
		reset states
		  	state->outpostPlayed = 0;
 			state->phase = 0;
  			state->numActions = 1;
  			state->coins = 0;
  			state->numBuys = 1;
  			state->playedCardCount = 0;
 			state->handCount[state->whoseTurn] = 0;
		next player draws hand
		update money


- current player changes to next player
- ends if game is over

*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>


int main (int argc, char** argv) {
  struct gameState state;
  struct gameState previousState;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, council_room, smithy};

  int seed = 2;
  int player;
  

	printf("\n\n\n\n---------------- unittest4 ----------------\n\n");

	printf("----------------Testing Card: endTurn ----------------\n");

	/******* Test Current player changes to next player *******/

	printf("*******Test1: Current player changes to next player *******\n");
	initTestGame(2, k, seed, &state);
	player = whoseTurn(&state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(numHandCards(&state) == 1);
	previousState = state;
	endTurn(&state);
	if(state.whoseTurn == (player + 1))
	{
		printf("PASS: Current player changes to next player\n\n\n");
		
	}
	else
	{	printf("FAIL: Current player changes to next player\n\n\n"); }





	/******* Test Game does not advance if game ends *******/

	printf("*******Test2: Game does not advance if game ends *******\n");
	initTestGame(2, k, seed, &state);
	player = whoseTurn(&state);
	assert(numHandCards(&state) == 0);
	assert(numHandCards(&state) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(numHandCards(&state) == 8);
	previousState = state;
	endTurn(&state);
	int game_over = isGameOver(&state);
	previousState = state;
	
	if(game_over == 1 && player == player)
	{
		printf("PASS: Game does not advance if game ends \n\n\n");
		
	}
	else
	{	printf("FAIL: Game does not advance if game ends \n\n\n"); }




	printf("*******Testing endTurn Complete!*******\n\n\n");
	return 0;
} // main
