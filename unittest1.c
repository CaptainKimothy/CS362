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









