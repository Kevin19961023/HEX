#include "stdafx.h"
#include "MoveGenerator.h"


CMoveGenerator::CMoveGenerator(void)
{
}


CMoveGenerator::~CMoveGenerator(void)
{
}

bool CMoveGenerator::IsValidMove(int (&map)[11][11],int x,int y)
{
	if (map[x][y] == 0)
	{
		return true;
	}
	return false;
}

int CMoveGenerator::AddMove(int x,int y,int side,int nPly)
{
	m_MoveList[nPly][m_nMoveCount].x = x;
	m_MoveList[nPly][m_nMoveCount].y = y;
	m_MoveList[nPly][m_nMoveCount].side = side;
	m_nMoveCount++;
	return m_nMoveCount;
}

int CMoveGenerator::AddVirtualConnectionMove(int x,int y,int side,int nPly)
{
	m_VirtualConMoveList[nPly][m_nVConMoveCount].x = x;
	m_VirtualConMoveList[nPly][m_nVConMoveCount].y = y;
	m_VirtualConMoveList[nPly][m_nVConMoveCount].side = side;
	m_nVConMoveCount++;
	return m_nVConMoveCount;
}

int CMoveGenerator::AddSemiVirtualConnectionMove(int x,int y,int side,int nPly)
{
	m_SemiVirtualMoveList[nPly][m_nSemiVirtualMoveCount].x = x;
	m_SemiVirtualMoveList[nPly][m_nSemiVirtualMoveCount].y = y;
	m_SemiVirtualMoveList[nPly][m_nSemiVirtualMoveCount].side = side;
	m_nSemiVirtualMoveCount++;
	return m_nSemiVirtualMoveCount;
}

//产生给定棋盘所有的合法的走法
int CMoveGenerator::CreatePossibleMove(Point (&CurVCNode)[N][4], int m_nCurVCNodeMount,int (&map)[11][11],int nPly,int nSide)
{
	int x,y;
	m_nMoveCount = 0;
	m_nVConMoveCount = 0;
	m_nSemiVirtualMoveCount = 0;
	m_nAllMoveCount = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((map[i][j] == 0) && (IsSemiVirtualConnection(map,i,j,nSide)!=-1) && (IsVirtualConnection(map,i,j,nSide)!=-1) )
			{
				AddSemiVirtualConnectionMove(i,j,nSide,nPly);
			}
			else if ((map[i][j] == 0) && (IsSemiVirtualConnection(map,i,j,nSide)!=-1) )
			{
				AddSemiVirtualConnectionMove(i,j,nSide,nPly);
			}
			else if ((map[i][j] == 0) && (IsVirtualConnection(map,i,j,nSide)!=-1) )
			{
				AddVirtualConnectionMove(i,j,nSide,nPly);
			}
			else if (map[i][j] == 0)
			{
				AddMove(i,j,nSide,nPly);
			}
		}
	}
	for (int i = 0; i < m_nSemiVirtualMoveCount; i++)
	{
		m_AllMoveList[nPly][m_nAllMoveCount].x = m_SemiVirtualMoveList[nPly][i].x;
		m_AllMoveList[nPly][m_nAllMoveCount].y = m_SemiVirtualMoveList[nPly][i].y;
		m_AllMoveList[nPly][m_nAllMoveCount].side = m_SemiVirtualMoveList[nPly][i].side;
		m_nAllMoveCount++;
	}
	for (int i = 0; i < m_nVConMoveCount; i++)
	{
		m_AllMoveList[nPly][m_nAllMoveCount].x = m_VirtualConMoveList[nPly][i].x;
		m_AllMoveList[nPly][m_nAllMoveCount].y = m_VirtualConMoveList[nPly][i].y;
		m_AllMoveList[nPly][m_nAllMoveCount].side = m_VirtualConMoveList[nPly][i].side;
		m_nAllMoveCount++;
	}
	for (int i = 0; i < m_nMoveCount; i++)
	{
		m_AllMoveList[nPly][m_nAllMoveCount].x = m_MoveList[nPly][i].x;
		m_AllMoveList[nPly][m_nAllMoveCount].y = m_MoveList[nPly][i].y;
		m_AllMoveList[nPly][m_nAllMoveCount].side = m_MoveList[nPly][i].side;
		m_nAllMoveCount++;
	}
	
	return m_nAllMoveCount;

}

int CMoveGenerator::IsVirtualConnection(int (&CurPosition)[11][11],int x,int y,int side)
{
	int mapSide;
	if (side == 0)//白====
	{
		mapSide = -1;
	}
	else if (side == 1)//黑
	{
		mapSide = 1;
	}
	
		//右下虚桥=右下+下+虚桥点
		if (x + 1<=10 && CurPosition[x+1][y] == 0 //右下
			&& CurPosition[x+1][y+1] == 0 && y+1<=10//下
			&& CurPosition[x+2][y+1] == mapSide && x+2 <=10//虚桥点
			)
		{
			return 1;
		}              
		//右虚桥=右下+右上+虚桥点
		if (x + 1<=10 && CurPosition[x+1][y] == 0 //右下
			&& CurPosition[x][y-1] == 0 && y-1>=0//右上
			&& CurPosition[x+1][y-1] == mapSide//虚桥点
			)
		{
			return 2;
		}

		//右上虚桥=上+右上+虚桥点
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] == 0 //上
			&& CurPosition[x][y-1] == 0//右上
			&& CurPosition[x-1][y-2] == mapSide && y-2 >=0//虚桥点
			)
		{
			return 3;
		}

		//左上虚桥=上+左上+虚桥点
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] == 0 //上
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-2][y-1] == mapSide && x-2 >=0//虚桥点
			)
		{
			return 4;
		}

		//左虚桥=左下+左上+虚桥点
		if (x - 1>=0 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-1][y+1] == mapSide//虚桥点
			)
		{
			return 5;
		}
		
		//左下虚桥=左下+下+虚桥点
		if (x + 1<=10 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x+1][y+1] == 0//下
			&& CurPosition[x+1][y+2] == mapSide && y+2<=10//虚桥点
			)
		{
			return 6;
		}
	return -1;
}

int CMoveGenerator::IsSemiVirtualConnection(int (&CurPosition)[11][11],int x,int y,int side)
{
	int mapSide;
	if (side == 0)//白====
	{
		mapSide = -1;
	}
	else if (side == 1)//黑
	{
		mapSide = 1;
	}
	
		//右下半虚桥=右下+下+虚桥点
	if (x + 1<=10 && CurPosition[x+1][y] != 0 && CurPosition[x+1][y] != mapSide //右下
			&& CurPosition[x+1][y+1] == 0 && y+1<=10//下
			&& CurPosition[x+2][y+1] == mapSide && x+2 <=10//虚桥点
			)
		{
			return 11;
		} 
		if (x + 1<=10 && CurPosition[x+1][y] == 0 //右下
			&& CurPosition[x+1][y+1] != 0 && CurPosition[x+1][y+1] != mapSide && y+1<=10//下
			&& CurPosition[x+2][y+1] == mapSide && x+2 <=10//虚桥点
			)
		{
			return 12;
		}
		//右虚桥=右下+右上+虚桥点
		if (x + 1<=10 && CurPosition[x+1][y] != 0 && CurPosition[x+1][y] != mapSide//右下
			&& CurPosition[x][y-1] == 0 && y-1>=0//右上
			&& CurPosition[x+1][y-1] == mapSide//虚桥点
			)
		{
			return 21;
		}
		if (x + 1<=10 && CurPosition[x+1][y] == 0//右下
			&& CurPosition[x][y-1] != 0 && y-1>=0 && CurPosition[x][y-1] != mapSide///右上
			&& CurPosition[x+1][y-1] == mapSide//虚桥点
			)
		{
			return 22;
		}

		//右上虚桥=上+右上+虚桥点
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] != 0 && CurPosition[x-1][y-1] != mapSide //上
			&& CurPosition[x][y-1] == 0//右上
			&& CurPosition[x-1][y-2] == mapSide && y-2 >=0//虚桥点
			)
		{
			return 31;
		}
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] ==0//上
			&& CurPosition[x][y-1] != 0 && CurPosition[x][y-1] != mapSide//右上
			&& CurPosition[x-1][y-2] == mapSide && y-2 >=0//虚桥点
			)
		{
			return 32;
		}

		//左上虚桥=上+左上+虚桥点
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] != 0 && CurPosition[x-1][y-1] != mapSide//上
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-2][y-1] == mapSide && x-2 >=0//虚桥点
			)
		{
			return 41;
		}
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] == 0 //上
			&& CurPosition[x-1][y] != 0 && CurPosition[x-1][y] != mapSide//左上
			&& CurPosition[x-2][y-1] == mapSide && x-2 >=0//虚桥点
			)
		{
			return 42;
		}

		//左虚桥=左下+左上+虚桥点
		if (x - 1>=0 && y + 1<=10 && CurPosition[x][y+1] != 0 && CurPosition[x][y+1] != mapSide //左下
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-1][y+1] == mapSide//虚桥点
			)
		{
			return 51;
		}
		if (x - 1>=0 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x-1][y] != 0 && CurPosition[x-1][y] != mapSide//左上
			&& CurPosition[x-1][y+1] == mapSide//虚桥点
			)
		{
			return 52;
		}
		
		//左下虚桥=左下+下+虚桥点
		if (x + 1<=10 && y + 1<=10 && CurPosition[x][y+1] != 0 && CurPosition[x][y+1] != mapSide//左下
			&& CurPosition[x+1][y+1] == 0//下
			&& CurPosition[x+1][y+2] == mapSide && y+2<=10//虚桥点
			)
		{
			return 61;
		}
		if (x + 1<=10 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x+1][y+1] != 0 && CurPosition[x+1][y+1] != mapSide//下
			&& CurPosition[x+1][y+2] == mapSide && y+2<=10//虚桥点
			)
		{
			return 62;
		}
	return -1;
}