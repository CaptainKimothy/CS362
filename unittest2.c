/*

getWinners -	set unused player scores to -9999
		set players score in sorted array
		set highscore
		see which players have high score
		set winners to 1 and others to 0


Cases to check to ensure pass:
- One player with high score
- More than one player with high score


*/


//#include "dominion.c"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
//#include "rngs.c"
#include <stdlib.h>
#include <assert.h>
#include <math.h>


int main (int argc, char** argv) {
  struct gameState state;
  struct gameState previousState;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, council_room, smithy};

  int seed = 2;
  
  int winner;
  int players[3] = {0, 0, 0};
  int numPlayers = 3;
  int player = 0;
  int winnerCount;
  int i;


	printf("\n\n\n\n---------------- unittest2 ----------------\n\n");
	printf("---------------- Testing Card: getWinners ----------------\n");

	/******* Test one player with high score *******/

	printf("******* Test1: one player with high score *******\n");

	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(numHandCards(&state) == 5);

	previousState = state;
	getWinners(players, &state);
	winnerCount = 0;
	for(i = 0; i < 4; i++)
	{
		if(players[i] == 1)
		{  winnerCount++;  }
	}

	if(winnerCount == 1)
	{
		printf("PASS: one player with high score\n\n\n");
		
	}
	else
	{	printf("FAIL: one player with high score\n\n\n"); }



	/******* Test two players with high score *******/

	printf("******* Test2: two players with high scores *******\n");
	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(numHandCards(&state) == 5);
	
	
	endTurn(&state);
	player = state.whoseTurn;
	state.discardCount[1] = 0;
	state.handCount[1] = 0;

	assert(numHandCards(&state) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);

	assert(numHandCards(&state) == 5);
	endTurn(&state);
	getWinners(players, &state); 
	
	winnerCount = 0;
	for(i = 0; i < 4; i++)
	{
		if(players[i] == 1)
		{  winnerCount++;  }
	}


	if(scoreFor(0, &state) == scoreFor(1, &state)) //winnerCount == 2)
	{
		printf("PASS: Two players with high scores\n\n\n");
		
	}
	else
	{	printf("FAIL: Two players with high scores\n\n\n"); }



	

	printf("*******Testing getWinners Complete!*******\n\n\n");
	return 0;
} // main
