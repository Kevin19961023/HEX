#pragma once

#include "Point.h"

class CHistory
{
public:
	CHistory(void);
	~CHistory(void);
	//����ʷ��¼�����
	void ResetHistoryTable0();
	//ȡĳһ�߷�����ʷ�÷�
	int GetHistoryScore0(Point move);
	//��ĳһ�߷�������ʷ��¼��
	void EnterHistoryScore0(Point move,int depth);
	//�Ӵ�С�Ե�ǰ�߷����н�������
	void PopSort0(Point* source,int n);


	//����ʷ��¼�����
	void ResetHistoryTable1();
	//ȡĳһ�߷�����ʷ�÷�
	int GetHistoryScore1(Point move);
	//��ĳһ�߷�������ʷ��¼��
	void EnterHistoryScore1(Point move,int depth);
	//�Ӵ�С�Ե�ǰ�߷����н�������
	void PopSort1(Point* source,int n);


	int m_HistoryTable0[11][11];//�׵���ʷ�÷ֱ�==========(m_nMaxDepth - depth)%2
	int m_HistoryTable1[11][11];//�ڵ���ʷ
};

