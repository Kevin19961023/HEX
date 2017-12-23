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
	CStack m_StackCurV;//����ջ��������ݹ�����ʱÿһ����CurV
	//int side;//1--��  0--��
	Point m_BestMove;//����߷�
	CMoveGenerator *m_pMG;
	CEveluation *m_pEval;
	CHistory m_history;
	int m_nSearchDepth;//����������
	int m_nMaxDepth;//��ǰ����������������
	int CurPosition[11][11];//��ǰ����Ľڵ�
	vector<CNode> CurV[N];//��ǰ�����·��
	Point CurVCNode[N][4];//��ǰ��������Žڵ��,�±�0��3λ�÷����ŵ�ͷ��β,1��2�����ŵ��м䲿��
	int m_nCurVCNodeMount;
	CSearchEngine(void);
	~CSearchEngine(void);
	//���Ľӿڣ�Ϊ��ǰ�����߳���һ��
	void SearchAGoodMove(int (&map)[11][11],vector<CNode> (&v)[N],Point (&VCNode)[N][4],int &mount);
	//��������������
	void SetSearchDepth(int nDepth){m_nSearchDepth = nDepth;};
	//�����߷�������
	void SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;};
	//���ù�ֵ����
	void SetEveluator(CEveluation *pEva){m_pEval = pEva;};
	//����ĳһ�߷���������֮�������
	void MakeMove(Point move,bool isBlack);
	//�ָ�
	void UnMakeMove(Point move,bool isBlack);
	void add_Node(int from,int to,int cap);
	bool isNewLinked(int currentNodeId,int nextNodeId);
	void UpdateSameSideNodes(int x,int y);//��Ժ������ͬһ��
	void UpdateOtherSideNodes(int x,int y);//��Ժ��������һ��
	void AddCurVCNode(Point move,bool isBlack);//�����ŵ���CurVCNode��
	//�ж��Ƿ����ʤ��
	int IsGameOver(int (&map)[11][11],int nDepth);
	//�����alpha-beta��֦
	int alpha_beta_search(int depth,int alpha,int beta);
	//��������ǿ��alpha-beta��֦
	CPattern Pattern_ab_search(int depth,int alpha,int beta);
};

