/*

isGameOver - 	if province cards are empty, game ends
		if three supply piles are at 0, game ends


- user gets all province cards 
- user empties 3 supply piles
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
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,sea_hag, council_room, smithy};

  int seed = 2;
  
  
  int game_over;
  int numPlayers = 2;
  int player = 0;


	printf("\n\n\n\n---------------- unittest3 ----------------\n\n");

	printf("----------------Testing Card: isGameOver ----------------\n");

	/******* Test province cards running out *******/

	printf("*******Test1: Province cards running out *******\n");
	initTestGame(2, k, seed, &state);
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
	game_over = isGameOver(&state);
	if(state.supplyCount[province] == 0 && game_over == 1)
	{
		printf("PASS: Province cards running out\n\n\n");
		
	}
	else
	{	printf("FAIL: Province cards running out\n\n\n"); }






	/******* Test Three supply piles empty *******/

	printf("*******Test2: Three supply piles empty *******\n");
	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);


	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);


	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);

	assert(numHandCards(&state) == 30);
	previousState = state;
	endTurn(&state);
	game_over = isGameOver(&state);

	int i;
	int j = 0;
  	for(i = 0; i < 25; i++)
    	{
      		if (state.supplyCount[i] == 0)
		{
	  		j++;
		}
    	}
  	
	
	if(j >= 3 && game_over == 1)
	{
		printf("PASS: Three supply piles empty\n\n\n");
		
	}
	else
	{	printf("FAIL: Three supply piles empty\n\n\n"); }




	


	printf("*******Testing isGameOver Complete!*******\n\n\n");
	return 0;
} // main
