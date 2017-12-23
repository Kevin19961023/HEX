#pragma once

#include "Point.h"
#define N 123
class CMoveGenerator
{
public:
	CMoveGenerator(void);
	~CMoveGenerator(void);
	//�����߷��Ƿ�Ϸ�
	static bool IsValidMove(int (&map)[11][11],int x,int y);
	//���������������еĺϷ����߷�
	int CreatePossibleMove(Point (&CurVCNode)[N][4], int m_nCurVCNodeMount,int (&map)[11][11],int nPly,int nSide);
	//���CreatePossibleMove�в����Ĳ����������߷��Ķ���
	Point m_MoveList[8][121];
	int m_nMoveCount;
	//���CreatePossibleMove�в����������߷��Ķ���
	Point m_VirtualConMoveList[8][121];
	int m_nVConMoveCount;
	//���CreatePossibleMove�в����������߷��Ķ���
	Point m_AllMoveList[8][121];
	int m_nAllMoveCount;
	//���CreatePossibleMove�в����İ������߷��Ķ���
	Point m_SemiVirtualMoveList[8][121];
	int m_nSemiVirtualMoveCount;

	int AddMove(int x,int y,int side,int nPly);
	int AddVirtualConnectionMove(int x,int y,int side,int nPly);
	int AddSemiVirtualConnectionMove(int x,int y,int side,int nPly);
	int IsVirtualConnection(int (&CurPosition)[11][11],int x,int y,int side);
	//�ж������Ѿ�����һ������һ����
	int IsSemiVirtualConnection(int (&CurPosition)[11][11],int x,int y,int side);
};

