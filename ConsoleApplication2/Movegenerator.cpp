#include"stdafx.h"

int PceDir[5][4] = {
	{ 0,0,0,0 },
{ 9,11,0,0 },
{ 9,11,-9,-11 },
{ -9,-11,0,0 },
{ 9,11,-9,-11 } };

int DirNum[5] = { 0,2,4,2,4 };
int Side;
vector<int>CapMoves;

//dfs type function to check store all possible capture and chain capture moves 
void GenCapMoves(BOARD *board, MOVE *MoveList, int Pce, int sq, int depth, int *deleted)
{
	for (int i = 0; i<DirNum[Pce]; i++)
	{
		int Dir = PceDir[Pce][i];
		if (board->Pieces[sq + Dir] != EMPTY && board->Pieces[sq + Dir] != OFF && PceCol[board->Pieces[sq + Dir]] != PceCol[Pce])
		{
			int NextPos = sq + Dir + Dir;
			if (board->Pieces[sq + Dir + Dir] == EMPTY && deleted[sq + Dir] == 0)
			{
				int OldPce = Pce;
				if (depth == 0 && deleted[sq] == 0)
					CapMoves.push_back(sq), deleted[sq] = 1;
				CapMoves.push_back(sq + Dir);
				CapMoves.push_back(NextPos);
				if (Pce == wP && (NextPos >= 81 && NextPos <= 88))
					Pce = wK;
				else if (Pce == bP && (NextPos >= 11 && NextPos <= 18))
					Pce = bK;
				deleted[sq + Dir] = 1;
				GenCapMoves(board, MoveList, Pce, NextPos, depth + 1, deleted);
				deleted[sq + Dir] = 0;
			}
		}
	}
	int flag = 0;
	for (int i = 0; i<DirNum[Pce]; i++)
	{
		int Dir = PceDir[Pce][i];
		if (board->Pieces[sq + Dir] != EMPTY && board->Pieces[sq + Dir] != OFF)
		{
			int col = PceCol[board->Pieces[sq + Dir]];
			if (PceCol[Pce] == board->Pieces[sq + Dir])
				continue;
			if (board->Pieces[sq + Dir + Dir] == EMPTY && deleted[sq + Dir] == 0)
			{
				flag = 1;
				break;
			}
		}
	}
	if (flag == 0 && depth>0)
	{
		MoveList->Move.push_back(CapMoves);
		MoveList->Count++;
	}
	if (depth>0)
	{
		CapMoves.pop_back();
		CapMoves.pop_back();
	}
}

//function to add diagonal moves which are no capture
void AddNonCapMove(MOVE *MoveList, int From, int To)
{
	vector<int>temp;
	temp.push_back(From);
	temp.push_back(To);
	MoveList->Move.push_back(temp);
	MoveList->Count++;
}


void GenMoves(BOARD *board, MOVE *MoveList)
{
	MoveList->Count = 0;
	Side = board->Side;

	for (int i = 0; i<100; i++)
	{
		int Pce = board->Pieces[i];
		if (Pce == EMPTY || Pce == OFF)
			continue;
		int Col = PceCol[Pce];
		if (Col != Side)
			continue;
		//generate no capture moves
		for (int j = 0; j<DirNum[Pce]; j++)
			if (board->Pieces[i + PceDir[Pce][j]] == EMPTY)
				AddNonCapMove(MoveList, i, i + PceDir[Pce][j]);

		//now generating capture moves for a side
		CapMoves.clear();
		int deleted[101] = { 0 };
		GenCapMoves(board, MoveList, Pce, i, 0, deleted);
	}
}

//print a given MoveList
void PrintMoveList(MOVE *MoveList)
{
	printf("Number Of Move : %d\n", MoveList->Count);
	int Size = MoveList->Count, count = 1;
	for (int i = 0; i<Size; i++)
	{
		printf("%d : ", count);
		vector<int>::iterator it;
		for (it = MoveList->Move[i].begin(); it != MoveList->Move[i].end(); it++)
			printf("%d,", *it);
		printf("\n");
		count++;
	}
}