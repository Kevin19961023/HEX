#include "stdafx.h"
#include "History.h"


CHistory::CHistory(void)
{
}


CHistory::~CHistory(void)
{
}

//将历史记录表清空
void CHistory::ResetHistoryTable0()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
			m_HistoryTable0[i][j] = 0;
	}
}

void CHistory::ResetHistoryTable1()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
			m_HistoryTable1[i][j] = 0;
	}
}
	//取某一走法的历史得分
	
int CHistory::GetHistoryScore0(Point move)
{
	return m_HistoryTable0[move.x][move.y];
}

int CHistory::GetHistoryScore1(Point move)
{
	return m_HistoryTable1[move.x][move.y];
}

	//将某一走法汇入历史记录表
	
void CHistory::EnterHistoryScore0(Point move,int depth)
{
	m_HistoryTable0[move.x][move.y] += 2<<depth;
}
	
void CHistory::EnterHistoryScore1(Point move,int depth)
{
	m_HistoryTable1[move.x][move.y] += 2<<depth;
}

//从大到小对当前走法队列进行排序
void CHistory::PopSort0(Point* source,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (m_HistoryTable0[source[i].x][source[i].y] < m_HistoryTable0[source[j].x][source[j].y])
			{
				Point temp = source[i];
				source[i] = source[j];
				source[j] = temp;
			}
		}
	}
}

void CHistory::PopSort1(Point* source,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (m_HistoryTable1[source[i].x][source[i].y] < m_HistoryTable1[source[j].x][source[j].y])
			{
				Point temp = source[i];
				source[i] = source[j];
				source[j] = temp;
			}
		}
	}
}