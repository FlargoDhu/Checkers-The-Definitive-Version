#include"stdafx.h"

//resets the board to all 0
void ResetBoard(BOARD *board)
{
	for (int i = 0; i<100; i++)
		board->Pieces[i] = OFF;

	for (int i = 0; i<64; i++)
		board->Pieces[sq64to100[i]] = EMPTY;

	board->HisPly = board->Ply = 0;
	for (int i = 0; i<5; i++)
		board->PceNum[i] = 0;
	board->PceVal[0] = board->PceVal[1] = 0;
	board->Side = WHITE;
}

void SetStart(BOARD *board)
{
	ResetBoard(board);
	//set up the white pieces 
	board->Pieces[sq64to100[1]] = board->Pieces[sq64to100[3]] = board->Pieces[sq64to100[5]] = board->Pieces[sq64to100[7]] = wP;
	board->Pieces[sq64to100[8]] = board->Pieces[sq64to100[10]] = board->Pieces[sq64to100[12]] = board->Pieces[sq64to100[14]] = wP;
	board->Pieces[sq64to100[17]] = board->Pieces[sq64to100[19]] = board->Pieces[sq64to100[21]] = board->Pieces[sq64to100[23]] = wP;

	//set up the black piieces
	board->Pieces[sq64to100[40]] = board->Pieces[sq64to100[42]] = board->Pieces[sq64to100[44]] = board->Pieces[sq64to100[46]] = bP;
	board->Pieces[sq64to100[49]] = board->Pieces[sq64to100[51]] = board->Pieces[sq64to100[53]] = board->Pieces[sq64to100[55]] = bP;
	board->Pieces[sq64to100[56]] = board->Pieces[sq64to100[58]] = board->Pieces[sq64to100[60]] = board->Pieces[sq64to100[62]] = bP;


	//updates the material value of the board 
	for (int i = 0; i<64; i++)
	{
		int sq = sq64to100[i];
		int Pce = board->Pieces[sq];
		int col = PceCol[Pce];
		board->PceVal[col] += PceVal[Pce];
		board->PceNum[Pce]++;
	}
	//to set up all the bitboards		
}

//print the board to the screen
void PrintBoard(BOARD *board)
{
	for (int i = 0; i<64; i++)
	{
		int sq = sq64to100[i];
		if (i % 8 == 0)
			printf("\n");
		printf("%c ", PceChar[board->Pieces[sq]]);
	}
	printf("\n\nSide To Move - %c\n", PceSideChar[board->Side]);
}