
// HexView.h : CHexView ��Ľӿ�
//

#pragma once
#include "Point.h"
#include "Eveluation.h"
#include "Node.h"
#include <vector> 
#include "SearchEngine.h"
#include "MoveGenerator.h"
#include "MoveGenerator.h"
using namespace std;

#define N 123 
#define INF 0x3f3f3f3f

class CHexView : public CView
{
protected: // �������л�����
	CHexView();
	DECLARE_DYNCREATE(CHexView)
public:
	
	Point HeadPoint[11][11];             //ͷ�ĵ�ַ
	Point HeartPoint[11][11];            //ÿ�������ε�����λ�á���������
	int map[11][11];                     //�����жϽ���ĺ��� 1--����   -1 --- ����   0--������
	int IsGo[11][11];                    //�����жϽ���ĺ��� 1--�߹�   -1----û�߹�
	void DrawHexPad(CDC *pDC);                   //��������
	double X ;                          //��ʾ�������εĵ��߳���20
	double flag;
	int start;                        //�������߽���ж���
	int Side;                         //�ж�����һ������ Side = 1;//��ʼ�Ǻڷ�����   1--�� 0--��
	int r;                            //����Բ�İ뾶
	int step;                         //�µ��ڼ���
	bool isFirst;                    //��¼�����Ⱥ���
	CEveluation eve;
	vector<CNode> v[N];					//��ͼ��·��
	vector<CNode> tempV[N];				//��ͼ��·��������������õ�
	bool used[N];

	Point VCNode[N][4];//��ǰ��������Žڵ��
	int m_nVCNodeMount;


	CSearchEngine m_SE;

	int dfs(int s,int t,int f);
	int max_flow(int s,int t);

	void add_Node(int from,int to,int cap);
	void CreateNodes();//����ͼ
	void UpdateSameSideNodes(int x,int y);
	void UpdateOtherSideNodes(int x,int y);
	bool isNewLinked(int currentNodeId,int nextNodeId);
	int IsVirtualConnection(int x,int y,int side);
	int IsSemiVirtualConnection(int x,int y,int side);//�жϰ�����
	void UpdateOtherSideVCNode(int x,int y);

	void Go(int x,int y,int side,int depth);               //�ݹ�Ѱ��·���ĺ���
	void IsBlackWin(int x,int y);
	void IsWhiteWin(int x,int y);
	bool IsWin;                      //��Ӯ�ж���

	//void 
// ����
public:
	CHexDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CHexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // HexView.cpp �еĵ��԰汾
inline CHexDoc* CHexView::GetDocument() const
   { return reinterpret_cast<CHexDoc*>(m_pDocument); }
#endif

