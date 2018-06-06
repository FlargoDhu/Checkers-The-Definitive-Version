#include"stdafx.h"
#define MATE 300000
#define INF 500000

vector<int>BestMove;

//the alphabeta search function in negamax fashion
static int AlphaBeta(int Alpha, int Beta, int Depth, BOARD *board)
{
	if (Depth == 0)
	{
		if (board->Side == WHITE)
			return board->PceVal[WHITE] - board->PceVal[BLACK];
		else
			return -1 * (board->PceVal[WHITE] - board->PceVal[BLACK]);
	}

	MOVE *list = new MOVE;
	GenMoves(board, list);

	int Legal = 0;
	int OldAlpha = Alpha;
	int Score = -INF;
	vector<int>temp;

	for (int i = 0; i<list->Count; i++)
	{
		MakeMove(board, list->Move[i]);
		Legal++;
		Score = -AlphaBeta(-Beta, -Alpha, Depth - 1, board);
		TakeMove(board);

		if (Score>Alpha)
		{
			if (Score >= Beta)
				return Beta;
			Alpha = Score;
			temp = list->Move[i];
		}
	}
	if (Legal == 0)
		return -MATE + board->Ply;

	if (OldAlpha != Alpha)
	{
		BestMove.clear();
		for (int i = 0; i<temp.size(); i++)
			BestMove.push_back(temp[i]);
	}
	return Alpha;
}

//function that return the best possible move or an empty vector if no move is possible
vector<int> SearchPos(BOARD *board, int MAXDEPTH)
{
	board->Ply = 0;
	BestMove.clear();
	int BestScore = AlphaBeta(-INF, INF, MAXDEPTH, board);
	return BestMove;
}