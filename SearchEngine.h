#pragma once

#include "MoveGenerator.h"
#include "Eveluation.h"
#include "Point.h"
#include "Pattern.h"
#include "Stack.h"
#include "History.h"
#include "TranspositionTable.h"

class CSearchEngine : public CTranspositionTable 
{
public:
	CStack m_StackCurV;//辅助栈，用来存递归搜索时每一步的CurV
	//int side;//1--黑  0--白
	Point m_BestMove;//最佳走法
	CMoveGenerator *m_pMG;
	CEveluation *m_pEval;
	CHistory m_history;
	int m_nSearchDepth;//最大搜索深度
	int m_nMaxDepth;//当前搜索的最大搜索深度
	int CurPosition[11][11];//当前局面的节点
	vector<CNode> CurV[N];//当前局面的路径
	Point CurVCNode[N][4];//当前局面的虚桥节点对,下标0和3位置放虚桥得头和尾,1和2放虚桥的中间部分
	int m_nCurVCNodeMount;
	CSearchEngine(void);
	~CSearchEngine(void);
	//博弈接口，为当前局面走出下一步
	void SearchAGoodMove(int (&map)[11][11],vector<CNode> (&v)[N],Point (&VCNode)[N][4],int &mount);
	//设置最大搜索深度
	void SetSearchDepth(int nDepth){m_nSearchDepth = nDepth;};
	//设置走法产生器
	void SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;};
	//设置估值引擎
	void SetEveluator(CEveluation *pEva){m_pEval = pEva;};
	//根据某一走法产生走了之后的棋盘
	void MakeMove(Point move,bool isBlack);
	//恢复
	void UnMakeMove(Point move,bool isBlack);
	void add_Node(int from,int to,int cap);
	bool isNewLinked(int currentNodeId,int nextNodeId);
	void UpdateSameSideNodes(int x,int y);//针对黑棋而言同一方
	void UpdateOtherSideNodes(int x,int y);//针对黑棋而言另一方
	void AddCurVCNode(Point move,bool isBlack);//加虚桥点入CurVCNode中
	//判断是否出现胜负
	int IsGameOver(int (&map)[11][11],int nDepth);
	//最基本alpha-beta剪枝
	int alpha_beta_search(int depth,int alpha,int beta);
	//论文中增强版alpha-beta剪枝
	CPattern Pattern_ab_search(int depth,int alpha,int beta);
};

