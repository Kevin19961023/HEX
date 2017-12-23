#pragma once

#include "Point.h"
#define N 123
class CMoveGenerator
{
public:
	CMoveGenerator(void);
	~CMoveGenerator(void);
	//检验走法是否合法
	static bool IsValidMove(int (&map)[11][11],int x,int y);
	//产生给定棋盘所有的合法的走法
	int CreatePossibleMove(Point (&CurVCNode)[N][4], int m_nCurVCNodeMount,int (&map)[11][11],int nPly,int nSide);
	//存放CreatePossibleMove中产生的不包括虚桥走法的队列
	Point m_MoveList[8][121];
	int m_nMoveCount;
	//存放CreatePossibleMove中产生的虚桥走法的队列
	Point m_VirtualConMoveList[8][121];
	int m_nVConMoveCount;
	//存放CreatePossibleMove中产生的所有走法的队列
	Point m_AllMoveList[8][121];
	int m_nAllMoveCount;
	//存放CreatePossibleMove中产生的半虚桥走法的队列
	Point m_SemiVirtualMoveList[8][121];
	int m_nSemiVirtualMoveCount;

	int AddMove(int x,int y,int side,int nPly);
	int AddVirtualConnectionMove(int x,int y,int side,int nPly);
	int AddSemiVirtualConnectionMove(int x,int y,int side,int nPly);
	int IsVirtualConnection(int (&CurPosition)[11][11],int x,int y,int side);
	//判断虚桥已经被另一方下了一个子
	int IsSemiVirtualConnection(int (&CurPosition)[11][11],int x,int y,int side);
};

