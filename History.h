#pragma once

#include "Point.h"

class CHistory
{
public:
	CHistory(void);
	~CHistory(void);
	//将历史记录表清空
	void ResetHistoryTable0();
	//取某一走法的历史得分
	int GetHistoryScore0(Point move);
	//将某一走法汇入历史记录表
	void EnterHistoryScore0(Point move,int depth);
	//从大到小对当前走法队列进行排序
	void PopSort0(Point* source,int n);


	//将历史记录表清空
	void ResetHistoryTable1();
	//取某一走法的历史得分
	int GetHistoryScore1(Point move);
	//将某一走法汇入历史记录表
	void EnterHistoryScore1(Point move,int depth);
	//从大到小对当前走法队列进行排序
	void PopSort1(Point* source,int n);


	int m_HistoryTable0[11][11];//白的历史得分表==========(m_nMaxDepth - depth)%2
	int m_HistoryTable1[11][11];//黑的历史
};

