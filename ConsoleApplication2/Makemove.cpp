#include"stdafx.h"

void MakeMove(BOARD *board, vector<int> Move)
{
	//set up the history arrays for takemove
	for (int i = 0; i<100; i++)
		board->History[board->HisPly].Pieces[i] = board->Pieces[i];
	for (int i = 0; i<5; i++)
		board->History[board->HisPly].PceNum[i] = board->PceNum[i];

	board->History[board->HisPly].Side = board->Side;
	board->History[board->HisPly].PceVal[0] = board->PceVal[0];
	board->History[board->HisPly].PceVal[1] = board->PceVal[1];
	board->HisPly++;
	board->Ply++;

	//now move a pieces from square to square...
	for (int i = 0; i + 1<Move.size(); i++)
	{
		int From = Move[i];
		int To = Move[i + 1];
		int Pce = board->Pieces[From];
		int OldPce = Pce;
		int Side = PceCol[OldPce];
		//check if the piece is promoted or not
		if (Pce == wP && (To >= 81 && To <= 88))
			Pce = wK;
		else if (Pce == bP && (To >= 11 && To <= 18))
			Pce = bK;

		//remove the old Pce from the board
		board->Pieces[From] = EMPTY;
		board->PceNum[OldPce]--;
		board->PceVal[Side] -= PceVal[OldPce];

		if (board->Pieces[To] != EMPTY)
		{
			int Pce2 = board->Pieces[To];
			ASSERT(PceCol[Pce2] != PceCol[OldPce]);
			board->Pieces[To] = EMPTY;
			board->PceNum[Pce2]--;
			board->PceVal[PceCol[Pce2]] -= PceVal[Pce2];
		}
		//add the new pce to the board
		board->Pieces[To] = Pce;
		board->PceNum[Pce]++;
		board->PceVal[Side] += PceVal[Pce];
	}
	//filp the side of the board;
	board->Side ^= 1;
}

//simply restore the board from the pHistory array to it immediate previous state
void TakeMove(BOARD *board)
{
	board->HisPly--;
	board->Ply--;
	for (int i = 0; i<100; i++)
		board->Pieces[i] = board->History[board->HisPly].Pieces[i];
	for (int i = 0; i<5; i++)
		board->PceNum[i] = board->History[board->HisPly].PceNum[i];

	board->PceVal[0] = board->History[board->HisPly].PceVal[0];
	board->PceVal[1] = board->History[board->HisPly].PceVal[1];
	board->Side = board->History[board->HisPly].Side;
}


//to check if a given move exists int the current movelist
int MoveExists(BOARD *board, vector<int>Move)
{
	int MoveSize = Move.size();
	int Count = 0;
	MOVE *MoveList = new MOVE;
	GenMoves(board, MoveList);
	for (int i = 0; i<MoveList->Count; i++)
		if (MoveList->Move[i].size() == MoveSize)
		{
			Count = 0;
			for (int j = 0; j<MoveList->Move[i].size(); j++)
				if (MoveList->Move[i][j] == Move[j])
					Count++;
			if (Count == MoveSize)
				return TRUE;
		}
	return FALSE;
}

//to convert the string input by the user to a move vector
vector<int>ParseMove(char* Inp)
{
	vector<int>Ans;
	int temp = 0;
	for (int i = 0; Inp[i] != '\0'; i++)
	{
		if (Inp[i] == ' ')
		{
			Ans.push_back(temp);
			temp = 0;
			continue;
		}
		int Num = Inp[i] - 48;
		temp = temp * 10 + Num;
	}
	Ans.push_back(temp);
	return Ans;
}