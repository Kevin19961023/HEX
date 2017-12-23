
// HexView.h : CHexView 类的接口
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
protected: // 仅从序列化创建
	CHexView();
	DECLARE_DYNCREATE(CHexView)
public:
	
	Point HeadPoint[11][11];             //头的地址
	Point HeartPoint[11][11];            //每个六边形的中心位置。从右向左
	int map[11][11];                     //辅助判断结果的函数 1--黑棋   -1 --- 白棋   0--无棋子
	int IsGo[11][11];                    //辅助判断结果的函数 1--走过   -1----没走过
	void DrawHexPad(CDC *pDC);                   //绘制棋盘
	double X ;                          //表示正六边形的单边长是20
	double flag;
	int start;                        //用来画边界的判断量
	int Side;                         //判断是哪一方下棋 Side = 1;//开始是黑方先下   1--黑 0--白
	int r;                            //画的圆的半径
	int step;                         //下到第几步
	bool isFirst;                    //记录黑棋先后手
	CEveluation eve;
	vector<CNode> v[N];					//存图的路径
	vector<CNode> tempV[N];				//存图的路径，求最大流会用到
	bool used[N];

	Point VCNode[N][4];//当前局面的虚桥节点对
	int m_nVCNodeMount;


	CSearchEngine m_SE;

	int dfs(int s,int t,int f);
	int max_flow(int s,int t);

	void add_Node(int from,int to,int cap);
	void CreateNodes();//创建图
	void UpdateSameSideNodes(int x,int y);
	void UpdateOtherSideNodes(int x,int y);
	bool isNewLinked(int currentNodeId,int nextNodeId);
	int IsVirtualConnection(int x,int y,int side);
	int IsSemiVirtualConnection(int x,int y,int side);//判断半虚桥
	void UpdateOtherSideVCNode(int x,int y);

	void Go(int x,int y,int side,int depth);               //递归寻找路径的函数
	void IsBlackWin(int x,int y);
	void IsWhiteWin(int x,int y);
	bool IsWin;                      //输赢判断量

	//void 
// 特性
public:
	CHexDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // HexView.cpp 中的调试版本
inline CHexDoc* CHexView::GetDocument() const
   { return reinterpret_cast<CHexDoc*>(m_pDocument); }
#endif

