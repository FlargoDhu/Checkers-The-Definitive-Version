#include "stdafx.h"

void PrintIndex()
{
	for (int i = 0; i<64; i++)
	{
		if (i % 8 == 0)
			printf("\n");
		printf("%d ", sq64to100[i]);
	}
	printf("\n");
}

void SelfPlay()
{
	printf("\n\n--------------The Bot Will Now Play itself to Some Randomized Depth-------------\n\n");
	printf("Press Any Key To See The Next Move\n");
	BOARD *board = new BOARD;
	SetStart(board);
	getchar();
	while (1)
	{
		MOVE *list = new MOVE;
		GenMoves(board, list);
		if (list->Count == 0)
		{
			printf("%c LOST THE GAME\n\n", PceSideChar[board->Side]);
			break;
		}
		int Depth = 4 + rand() %3;
		vector<int>BestMove = SearchPos(board, Depth);
		PrintBoard(board);
		MakeMove(board, BestMove);
		getchar();
	}
	StartGame();
}


void PlayBot()
{
	printf("\n\nPress '1' to see possible moves\n\n");
	printf("Press '0' to see number grid\n\n");
	BOARD *board = new BOARD;
	SetStart(board);
	printf("The Starting Board\n\n");
	PrintBoard(board);
	char Inp[200];
	int Side;
	printf("\nChoose Your Side...\n\n0. For Black\n1. For White\n");
	scanf_s("%d", &Side);
	if (Side == 0)
	{
		MOVE *list1 = new MOVE;
		GenMoves(board, list1);
		vector<int>BestMove1 = SearchPos(board, 8);
		MakeMove(board, BestMove1);
		PrintBoard(board);
	}
	while (1)
	{
		printf("\n\nEnter Your Move\n");
		getchar();
		scanf_s("%[^\n]", &Inp);
		if (Inp[0] == '0')
		{
			PrintIndex();
			continue;
		}
		else if (Inp[0] == '1')
		{
			printf("\nYour Possible MoveList is\n");
			MOVE *YourMoveList = new MOVE;
			GenMoves(board, YourMoveList);
			PrintMoveList(YourMoveList);
		}
		vector<int>Move = ParseMove(Inp);
		if (MoveExists(board, Move))
			MakeMove(board, Move);
		else
		{
			MOVE *User = new MOVE;
			GenMoves(board, User);
			if (User->Count == 0)
			{
				printf("Sorry You Lost\n\n");
				break;
			}
			else
				printf("Invalid Move...Enter Again\n\n");
			continue;
		}
		PrintBoard(board);
		printf("-----------------------------------Bot's Turn----------------------------------\n");
		MOVE *Bot = new MOVE;
		GenMoves(board, Bot);
		if (Bot->Count == 0)
		{
			printf("--------------------------Congratulations You Win--------------------------\n");
			break;
		}
		vector<int>BestMove = SearchPos(board, 8);
		MakeMove(board, BestMove);
		PrintBoard(board);
	}
	StartGame();
}