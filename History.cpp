#include "stdafx.h"
#include "History.h"


CHistory::CHistory(void)
{
}


CHistory::~CHistory(void)
{
}

//����ʷ��¼�����
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
	//ȡĳһ�߷�����ʷ�÷�
	
int CHistory::GetHistoryScore0(Point move)
{
	return m_HistoryTable0[move.x][move.y];
}

int CHistory::GetHistoryScore1(Point move)
{
	return m_HistoryTable1[move.x][move.y];
}

	//��ĳһ�߷�������ʷ��¼��
	
void CHistory::EnterHistoryScore0(Point move,int depth)
{
	m_HistoryTable0[move.x][move.y] += 2<<depth;
}
	
void CHistory::EnterHistoryScore1(Point move,int depth)
{
	m_HistoryTable1[move.x][move.y] += 2<<depth;
}

//�Ӵ�С�Ե�ǰ�߷����н�������
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