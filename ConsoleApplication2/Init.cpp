#include"stdafx.h"

int sq100to64[100];
int sq64to100[64];

//arays which will use enum values as index to get the respective value
char PceChar[5] = { '.','w','W','b','B' };
char PceSideChar[2] = { 'B','W' };
int PceVal[5] = { 0,100,500,100,500 };
int PceCol[5] = { RED,WHITE,WHITE,BLACK,BLACK };

//initialize the conversion array
void Init()
{
	for (int i = 0; i<100; i++)
		sq100to64[i] = OFF;
	int sq = 0;
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			int temp = Convert(i, j);
			sq64to100[sq] = temp;
			sq100to64[temp] = sq;
			sq++;
		}
}

void StartGame()
{
	int Choice;
	printf("Enter :\n1. To Watch The Bot Play Itself\n");
	printf("2. To Play With The Bot\n");
	printf("3. To Quit\n");
	scanf_s("%d", &Choice);
	if (Choice == 1)
		SelfPlay();
	else if (Choice == 2)
		PlayBot();
	else if (Choice == 3)
		printf("\n---------------------------------Hope You Enjoyed---------------------------------\n");
}