
// HexView.cpp : CHexView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Hex.h"
#endif

#include "HexDoc.h"
#include "HexView.h"
#include "math.h"
#include <iostream>
using namespace std;
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CHexView

IMPLEMENT_DYNCREATE(CHexView, CView)

BEGIN_MESSAGE_MAP(CHexView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHexView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CHexView ����/����

CHexView::CHexView()
{
	// TODO: �ڴ˴���ӹ������
	isFirst = false;
	IsWin = false;
	flag = sqrt(3.0);
	X = 20.0;
	start = 10;
	Side = -1;                     //��ʼ�Ǻڷ���������
	r = 30;
	step = 1;
	memset(v,0,sizeof(v));
	//ͷ��λ�õĳ�ʼ��
	for (int i = 0; i < 11; i++)
	{
		HeadPoint[i][0].y = i * 2 * flag * X;
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			map[i][j] = 0;                                         //1--����   -1 --- ����   0--������
			IsGo[i][j] = -1;                                       //1--�߹�   -1----û�߹�
			HeadPoint[i][j].x = 700 - j * 3 * X;
			if (j > 0)
			   HeadPoint[i][j].y = HeadPoint[i][j-1].y + (flag+1.8) * 10;
		}
	}
	//����λ�õĳ�ʼ����
	for (int i = 0; i<11; i++)
	{
		HeartPoint[i][0].x = (700 + X) + i * 3 * X;
		HeartPoint[i][0].y = (i + 1) * flag  * X;
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			HeartPoint[i][j].x = HeartPoint[i][j - 1].x - 3 * X;
			HeartPoint[i][j].y = HeartPoint[i][j - 1].y + flag * X;
		}
	}

	//����ͼ
	CreateNodes();
	//���ŶԸ���
	m_nVCNodeMount = 0;


	//��ʼ����
	CMoveGenerator *pMG = new CMoveGenerator();
	CEveluation *pEvel = new CEveluation();
	m_SE.SetEveluator(pEvel);
	m_SE.SetMoveGenerator(pMG);
	m_SE.SetSearchDepth(3);

	//ȷ���Ⱥ���
	int temp = MessageBox(_T("��ȷ��Ҫ������"), _T("�Ⱥ���ȷ������"), MB_OKCANCEL | MB_ICONQUESTION);
	if (temp != IDOK)
	{
		//��ʼ����һ����
		isFirst = true;
		map[5][5] = 1;
		UpdateSameSideNodes(5,5);
		step++;
	}
}

void CHexView::DrawHexPad(CDC * pDC)            //����Hex����
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(240, 230, 140));
	CPen *Pen = new CPen(PS_SOLID,3,RGB(0,0,0));                    //�ڱ�
	CPen *WhitePen = new CPen(PS_SOLID,3,RGB(255,255,255));         //�ױ�
	pDC->SelectObject(Pen);
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i+j < 11)
			{
				pDC->MoveTo(HeadPoint[i][j].x, HeadPoint[i][j].y);
				pDC->LineTo((HeadPoint[i][j].x + 2 * X), HeadPoint[i][j].y);
				pDC->LineTo((HeadPoint[i][j].x + 3 * X), flag * X + HeadPoint[i][j].y);
				pDC->LineTo((HeadPoint[i][j].x + 2 * X), 2 * flag * X + HeadPoint[i][j].y);
				if (j == start)
				{
					pDC->SelectObject(WhitePen);
					start -= 1;
					if (start < 0)
					{
						start = 10;
					}
				}
				pDC->LineTo((HeadPoint[i][j].x), 2 * flag * X + HeadPoint[i][j].y);
				pDC->LineTo((HeadPoint[i][j].x - X), flag * X + HeadPoint[i][j].y);
				pDC->SelectObject(Pen);
				pDC->LineTo((HeadPoint[i][j].x), HeadPoint[i][j].y);
				//�����ǻ��ԳƵ��������̵�
				if (i == 0)
				{
					pDC->SelectObject(WhitePen);
				}
				pDC->MoveTo((HeadPoint[i][j].x + j*6*X), HeadPoint[i][j].y);
				pDC->LineTo((HeadPoint[i][j].x + 2 * X + j * 6 * X), HeadPoint[i][j].y);
				pDC->LineTo((HeadPoint[i][j].x + 3 * X + j * 6 * X), flag * X + HeadPoint[i][j].y);
				pDC->SelectObject(Pen);
				pDC->LineTo((HeadPoint[i][j].x + 2 * X + j * 6 * X), 2 * flag * X + HeadPoint[i][j].y);
				if (i == 10 && j == 0)
				{
					pDC->SelectObject(WhitePen);
				}
				pDC->LineTo((HeadPoint[i][j].x + j * 6 * X), 2 * flag * X + HeadPoint[i][j].y);
				pDC->LineTo((HeadPoint[i][j].x - X + j * 6 * X), flag * X + HeadPoint[i][j].y);
				pDC->SelectObject(Pen);
				pDC->LineTo((HeadPoint[i][j].x + j * 6 * X), HeadPoint[i][j].y);
			}
		}
	}
}


CHexView::~CHexView()
{
}

BOOL CHexView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CHexView ����

void CHexView::OnDraw(CDC* pDC)
{
	CHexDoc* pDoc = GetDocument();
	DrawHexPad(pDC);
	
	
	if (isFirst)
	{
		pDC->SelectObject(new CBrush(RGB(0, 0, 0)));
		pDC->Ellipse(HeartPoint[5][5].x - r, HeartPoint[5][5].y - r, HeartPoint[5][5].x + r, HeartPoint[5][5].y + r);
	}
	


	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CHexView ��ӡ


void CHexView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHexView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CHexView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CHexView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CHexView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHexView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHexView ���

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHexDoc* CHexView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHexDoc)));
	return (CHexDoc*)m_pDocument;
}
#endif //_DEBUG

//�������÷���

int CHexView::dfs(int s,int t,int f)  
{  
    if(s>=t)  
        return f;  
    used[s]=true;  
    for(int i=0;i<tempV[s].size();i++)  
    {  
        CNode &tmp = tempV[s][i];  //ע��  
        if(used[tmp.to]==false && tmp.cap>0)  
        {  
            int d=dfs(tmp.to,t,min(f,tmp.cap));  
			if(d>0)  
            {  
                tmp.cap-=d;  
                tempV[tmp.to][tmp.rev].cap+=d;  
                return d;  
            }  
        }  
    }  
    return 0;  
}  
  
int CHexView::max_flow(int s,int t)  
{  
    int flow=0;  
    for(;;){  
        memset(used,false,sizeof(used));  
        int f=dfs(s,t,INF);  
        if(f==0)  
            return flow;  
        flow+=f;  
    }  
}  

// CHexView ��Ϣ�������


void CHexView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bool Flag = false;
	//�жϵ���ĵ��ںδ���
	int i, j;
	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 11; j++)
		{
			if ((HeartPoint[i][j].x - r < point.x) && (HeartPoint[i][j].x + r > point.x) && (HeartPoint[i][j].y - r < point.y) && (HeartPoint[i][j].y + r > point.y))
			{
				Flag = true;
			}
			if (Flag)
			{
				break;                                             //�жϵ�����ĵ�ͱ��������ֳ������ݳ�ȥHeartPoint����Ϣ
			}
		}
		if (Flag)
		{
			break;
		}
	}
	if (Flag)
	{
		CDC *pDC = GetDC();
		if (Side == 1)
		{
			pDC->SelectObject(new CBrush(RGB(0, 0, 0)));
			pDC->Ellipse(HeartPoint[i][j].x - r, HeartPoint[i][j].y - r, HeartPoint[i][j].x + r, HeartPoint[i][j].y + r);
			map[i][j] = 1;
			UpdateSameSideNodes(i,j);
			IsBlackWin(i, j);
			if (IsWin)
			{
				MessageBox(CString("�����ʤ!"));
			}
			/*
			Side *= -1;
			if (step >= 1)
			{
				
				stringstream os;
				for (int i = 0; i < N; i++)
				{
					tempV[i] = v[i];
				}
				os << max_flow(0,122);
				string str = os.str();
				CString cstr;
				cstr = str.c_str();
				MessageBox((_bstr_t)cstr);
			}*/
			
			step++;
			cout<<step;
		}
		else
		{
			
			pDC->SelectObject(new CBrush(RGB(255, 255, 255)));
			pDC->Ellipse(HeartPoint[i][j].x - r, HeartPoint[i][j].y - r, HeartPoint[i][j].x + r, HeartPoint[i][j].y + r);
			map[i][j] = -1;
			UpdateOtherSideNodes(i,j);
			IsWhiteWin(i, j);
			UpdateOtherSideVCNode(i,j);
			if (IsWin)
			{
				MessageBox(CString("�����ʤ!"));
			}
			//Side *= -1;
			int ii;
			int jj;
			if (step == 1)
			{
				if (map[5][5] == 0)
				{
					ii = 5;
					jj = 5;
				}
				else
				{
					ii = 6;
					jj = 5;
				}
			}
			else
			{
				m_SE.SearchAGoodMove(map,v,VCNode,m_nVCNodeMount);
				Point t_Point = m_SE.m_BestMove;
				ii = t_Point.x;
				jj = t_Point.y;
			}
			pDC->SelectObject(new CBrush(RGB(0, 0, 0)));
			map[ii][jj] = 1;
			pDC->Ellipse(HeartPoint[ii][jj].x - r, HeartPoint[ii][jj].y - r, HeartPoint[ii][jj].x + r, HeartPoint[ii][jj].y + r);
			IsBlackWin(i, j);
			if (IsWin)
			{
				MessageBox(CString("�����ʤ!"));
			}
			step++;
		}
	}
	Flag = false;
	IsWin = false;
	CView::OnLButtonDown(nFlags, point);
}

void CHexView::Go(int x, int y, int side, int depth)
{
	if (side == 1)
	{
		if (depth >= 10)
		{
			IsWin =  true;
			return;
		}
		//����c
		if ((x == 0)&&(y == 0))
		{
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth);
			}               //����
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1);
			}
		}
		//�����c
		if ((x == 0)&&(y == 10))
		{
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth);
			}                //����
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			
		}
		//����߅
		if ((x == 0)&&(y > 0))
		{
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth);
			}                //����
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth);
			}               //����
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1);
			}              //��
		}
		//����߅
		if ((x > 0)&&(y == 0))
		{
			
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth);
			}               //����
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1);
			}               //��
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1);
			}//����
		}
		//���±�
		if ((x > 0)&&(y == 10))
		{
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1);
			}//����
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth);
			}                //����
			if (map[x - 1][y - 1] == 1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				Go(x - 1, y - 1, side, depth - 1);
			}//��  
		}
		//���g�c
		if ((x > 0)&&(y > 0))
		{
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1);
			}//����
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth);
			}                //����
			if (map[x - 1][y - 1] == 1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				Go(x - 1, y - 1, side, depth - 1);
			}//��  
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth);
			}               //����
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1);
			}               //��
		}

	}
	else
	{
		if (depth >= 10)
		{
			IsWin =  true;
			return;
		}
		//����c
		if ((x == 0)&&(y == 0))
		{
			if (map[x][y + 1] == -1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth);
			}               //����
			if (map[x+1][y] == -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x + 1][y + 1] == -1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1);
			}
		}
		//�����c
		if ((x == 0)&&(y == 10))
		{
			if (map[x][y - 1] == -1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth);
			}                //����
			if (map[x+1][y] == -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			
		}
		//����߅
		if ((x == 0)&&(y > 0))
		{
			if (map[x][y - 1] == -1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth);
			}                //����
			if (map[x+1][y] == -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x][y + 1] == -1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth);
			}               //����
			if (map[x + 1][y + 1] == -1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1);
			}              //��
		}
		//����߅
		if ((x > 0)&&(y == 0))
		{
			
			if (map[x+1][y] == -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x][y + 1] == -1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth);
			}               //����
			if (map[x + 1][y + 1] == -1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1);
			}               //��
			if (map[x - 1][y] == -1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1);
			}//����
		}
		//���±�
		if ((x > 0)&&(y == 10))
		{
			if (map[x+1][y] == -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x - 1][y] == -1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1);
			}//����
			if (map[x][y - 1] == -1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth);
			}                //����
			if (map[x - 1][y - 1] == -1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				Go(x - 1, y - 1, side, depth - 1);
			}//��  
		}
		//���g�c
		if ((x > 0)&&(y > 0))
		{
			if (map[x+1][y] == -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1);
			}              //����
			if (map[x - 1][y] == -1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1);
			}//����
			if (map[x][y - 1] == -1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth);
			}                //����
			if (map[x - 1][y - 1] == -1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				Go(x - 1, y - 1, side, depth - 1);
			}//��  
			if (map[x][y + 1] == -1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth);
			}               //����
			if (map[x + 1][y + 1] == -1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1);
			}               //��
		}

	}
}

void CHexView::IsBlackWin(int x,int y)               //�������壺map���±�
{
	IsWin = false;
	for (int i = 0; i < 11; i++)
	{
		if (map[0][i] == 1)
		{
			IsGo[0][i] = 1;
			Go(0, i, 1, 0);
			for (int k = 0; k < 11; k++)                   //ÿ�α�����ɻָ�IsGo����
			{
				for (int g = 0; g < 11; g++)
				{
					IsGo[k][g] = -1;
				}
			}
		}
	}
}

void CHexView::IsWhiteWin(int x, int y)               //�������壺map���±�
{
	IsWin = false;
	for (int i = 0; i < 11; i++)
	{
		if (map[i][0] == -1)
		{
			IsGo[i][0] = 1;
			Go(i, 0, -1, 0);
			for (int k = 0; k < 11; k++)                   //ÿ�α�����ɻָ�IsGo����
			{
				for (int g = 0; g < 11; g++)
				{
					IsGo[k][g] = -1;
				}
			}
		}
	}
}

void CHexView::add_Node(int from,int to,int cap)
{
	v[from].push_back(CNode(to,cap,v[to].size()));  
    v[to].push_back(CNode(from,0,v[from].size()-1));  
}

void CHexView::CreateNodes()
{
	int nodeNo;
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			nodeNo = x*11 + (y+1);
			//����c
			if ((x == 0)&&(y == 0))
			{
				add_Node(0,nodeNo,INF);
				add_Node(1,12,1);
				add_Node(1,13,1);
			}
			//�����c
			if ((x == 0)&&(y == 10))
			{
				add_Node(0,nodeNo,INF);
				add_Node(11,10,1);
				add_Node(11,22,1);
			}
			//����߅
			if ((x == 0)&&(y > 0)&&(y < 10))
			{
				//�õ����y+1
				//nodeNo = y + 1;
				add_Node(0,nodeNo,INF);
				add_Node(nodeNo,nodeNo - 1,1);//����
				add_Node(nodeNo,nodeNo + 11,1);//����
				add_Node(nodeNo,nodeNo + 12,1);//��
			}
			//����߅
			if ((x > 0)&&(x < 10)&&(y == 0))
			{
				//�õ����x*11+1
				//nodeNo = x*11 + 1;
				add_Node(nodeNo,nodeNo + 11,1);//����
				add_Node(nodeNo,nodeNo + 12,1);//��
			}
			//���±�
			if ((x > 0)&&(x < 10)&&(y == 10))
			{
				//�õ����(x+1)*11
				//nodeNo = (x+1)*11;
				add_Node(nodeNo,nodeNo - 1,1);//����
				add_Node(nodeNo,nodeNo + 11,1);//����
			}
			//���g�c
			if ((x > 0)&&(x < 10)&&(y > 0)&&(y < 10))
			{
				//�õ����x*11+(y+1)
				//nodeNo = x*11 + (y+1);
				add_Node(nodeNo,nodeNo - 1,1);//����
				add_Node(nodeNo,nodeNo + 11,1);//����
				add_Node(nodeNo,nodeNo + 12,1);//��
			}
			//����c
			if ((x == 10)&&(y == 10))
			{
				//�õ����121
				//nodeNo = 121;
				add_Node(nodeNo,122,INF);
				add_Node(nodeNo,nodeNo - 1,1);//����
			}
			//�����c
			if ((x == 10)&&(y == 0))
			{
				//�õ����111
				//nodeNo = 111;
				add_Node(nodeNo,122,INF);
			}
			//����߅
			if ((x == 10)&&(y > 0)&&(y < 10))
			{
				//�õ����y+1
				//nodeNo = x*11 + (y+1);
				add_Node(nodeNo,122,INF);
				add_Node(nodeNo,nodeNo - 1,1);//����				
			}
		}
	}

}

void CHexView::UpdateSameSideNodes(int x,int y)
{
	int currentNodeId = x*11 + (y+1);
	vector<int> nextNodesId;
	vector<int> preNodesId;
	for (int i = 0; i < v[currentNodeId].size(); i++)
	{
		if (v[currentNodeId][i].to == -1)
		{
			continue;
		}
		if(v[currentNodeId][i].to == 0)//Դ��
		{
			preNodesId.push_back(0);
		}
		else if (v[currentNodeId][i].to == currentNodeId + 1)//����
		{
			preNodesId.push_back(v[currentNodeId][i].to);  
		}
		else if ((v[currentNodeId][i].to > currentNodeId)||(v[currentNodeId][i].to == currentNodeId - 1))//�Һ����� || ����
		{
			nextNodesId.push_back(v[currentNodeId][i].to);  
		}
		else if (v[currentNodeId][i].to < currentNodeId)//�ϣ�����
		{
			preNodesId.push_back(v[currentNodeId][i].to);  
		}
	}
	for (int i = 0; i < preNodesId.size(); i++)
	{
		//ɾȥ��ǰ�ڵ�ǰ��ڵ���ָ��ɾȥ�ڵ��·��
		int t = preNodesId[i];
		for (int j = 0; j < v[t].size(); j++)
		{
			if (v[t][j].to == currentNodeId)
			{
				v[t][j].to = -1;
				v[t][j].cap = -1;
				v[t][j].rev = -1;
			}
		}
		
		
		
		//����ǰ��ڵ�ָ�����ڵ��·��
		for (int j = 0; j < nextNodesId.size(); j++)
		{
			if(isNewLinked(t,nextNodesId[j]))
				add_Node(preNodesId[i],nextNodesId[j],1);  
		}

	}
	//ɾȥ����ڵ���ָ��ǰ�ڵ�ķ���·��
	for (int i = 0; i < nextNodesId.size(); i++)
	{
		//ɾȥ��ǰ�ڵ����ڵ�ָ��ɾȥ�ڵ��·��
		int t = nextNodesId[i];
		for (int j = 0; j < v[t].size(); j++)
		{
			if (v[t][j].to == currentNodeId)
			{
				v[t][j].to = -1;
				v[t][j].cap = -1;
				v[t][j].rev = -1;
			}
		}
	}

	//ɾȥ��ǰ�ڵ����Ϣ
	vector<CNode> newTemp;
	v[currentNodeId] = newTemp;

}

void CHexView::UpdateOtherSideNodes(int x,int y)
{
	int currentNodeId = x*11 + (y+1);
	vector<int> updateNodesId;
	for (int i = 0; i < v[currentNodeId].size(); i++)
	{
		updateNodesId.push_back(v[currentNodeId][i].to);  	
	}
	for (int i = 0; i < updateNodesId.size(); i++)
	{
		//ɾȥ��ؽڵ�ָ��ɾȥ�ڵ��·��
		int t = updateNodesId[i];
		for (int j = 0; j < v[t].size(); j++)
		{
			if (v[t][j].to == currentNodeId)
			{
				v[t][j].to = -1;
				v[t][j].cap = -1;
				v[t][j].rev = -1;
			}
		}
		
	}

	//ɾȥ��ǰ�ڵ����Ϣ
	vector<CNode> newTemp;
	v[currentNodeId] = newTemp;

}

bool CHexView::isNewLinked(int currentNodeId,int nextNodeId)
{
	for (int i = 0; i < v[currentNodeId].size(); i++)
	{
		if (v[currentNodeId][i].to == nextNodeId)
		{
			return false;
		}
	}
	return true;
}

int CHexView::IsVirtualConnection(int x,int y,int side)
{
	int mapSide;
	int nResultNum = 0;
	if (side == 0)//��====
	{
		mapSide = -1;
	}
	else if (side == 1)//��
	{
		mapSide = 1;
	}
	
		//��������=����+��+���ŵ�
		if (x + 1<=10 && map[x+1][y] == 0 //����
			&& map[x+1][y+1] == 0 && y+1<=10//��
			&& map[x+2][y+1] == mapSide && x+2 <=10//���ŵ�
			)
		{
			Point p1(x,y,side);
			Point p2(x+1,y,-1);
			Point p3(x+1,y+1,-1);
			Point p4(x+2,y+1,side);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}              
		//������=����+����+���ŵ�
		if (x + 1<=10 && map[x+1][y] == 0 //����
			&& map[x][y-1] == 0 && y-1>=0//����
			&& map[x+1][y-1] == mapSide//���ŵ�
			)
		{
			Point p1(x,y,side);
			Point p2(x+1,y,-1);
			Point p3(x,y-1,-1);
			Point p4(x+1,y-1,side);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}

		//��������=��+����+���ŵ�
		if (x - 1>=0 && y - 1>=0 && map[x-1][y-1] == 0 //��
			&& map[x][y-1] == 0//����
			&& map[x-1][y-2] == mapSide && y-2 >=0//���ŵ�
			)
		{
			Point p1(x,y,side);
			Point p2(x-1,y-1,-1);
			Point p3(x,y-1,-1);
			Point p4(x-1,y-2,side);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}

		//��������=��+����+���ŵ�
		if (x - 1>=0 && y - 1>=0 && map[x-1][y-1] == 0 //��
			&& map[x-1][y] == 0//����
			&& map[x-2][y-1] == mapSide && x-2 >=0//���ŵ�
			)
		{
			Point p1(x,y,side);
			Point p2(x-1,y-1,-1);
			Point p3(x-1,y,-1);
			Point p4(x-2,y-1,side);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}

		//������=����+����+���ŵ�
		if (x - 1>=0 && y + 1<=10 && map[x][y+1] == 0 //����
			&& map[x-1][y] == 0//����
			&& map[x-1][y+1] == mapSide//���ŵ�
			)
		{
			Point p1(x,y,side);
			Point p2(x-1,y,-1);
			Point p3(x,y+1,-1);
			Point p4(x-1,y+1,side);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
		
		//��������=����+��+���ŵ�
		if (x + 1<=10 && y + 1<=10 && map[x][y+1] == 0 //����
			&& map[x+1][y+1] == 0//��
			&& map[x+1][y+2] == mapSide && y+2<=10//���ŵ�
			)
		{
			Point p1(x,y,side);
			Point p2(x+1,y+1,-1);
			Point p3(x,y+1,-1);
			Point p4(x+1,y+2,side);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
	return nResultNum;
}

int CHexView::IsSemiVirtualConnection(int x,int y,int side)
{
	int mapSide;
	int nResultNum = 0;
	if (side == 0)//��====
	{
		mapSide = -1;
	}
	else if (side == 1)//��
	{
		mapSide = 1;
	}
	
		//���°�����=����+��+���ŵ�
		if (x + 1<=10 && map[x+1][y] != 0 && map[x+1][y] != mapSide //����
			&& map[x+1][y+1] == 0 && y+1<=10//��
			&& map[x+2][y+1] == mapSide && x+2 <=10//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x+1,y,1);
			Point p3(x+1,y+1,-1);
			Point p4(x+2,y+1,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		} 
		if (x + 1<=10 && map[x+1][y] == 0 //����
			&& map[x+1][y+1] != 0 && map[x+1][y+1] != mapSide && y+1<=10//��
			&& map[x+2][y+1] == mapSide && x+2 <=10//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x+1,y,-1);
			Point p3(x+1,y+1,1);
			Point p4(x+2,y+1,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
		//������=����+����+���ŵ�
		if (x + 1<=10 && map[x+1][y] != 0 && map[x+1][y] != mapSide//����
			&& map[x][y-1] == 0 && y-1>=0//����
			&& map[x+1][y-1] == mapSide//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x+1,y,1);
			Point p3(x,y-1,-1);
			Point p4(x+1,y-1,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
		if (x + 1<=10 && map[x+1][y] == 0//����
			&& map[x][y-1] != 0 && y-1>=0 && map[x][y-1] != mapSide///����
			&& map[x+1][y-1] == mapSide//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x+1,y,-1);
			Point p3(x,y-1,1);
			Point p4(x+1,y-1,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}

		//��������=��+����+���ŵ�
		if (x - 1>=0 && y - 1>=0 && map[x-1][y-1] != 0 && map[x-1][y-1] != mapSide //��
			&& map[x][y-1] == 0//����
			&& map[x-1][y-2] == mapSide && y-2 >=0//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x-1,y-1,1);
			Point p3(x,y-1,-1);
			Point p4(x-1,y-2,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
		if (x - 1>=0 && y - 1>=0 && map[x-1][y-1] ==0//��
			&& map[x][y-1] != 0 && map[x][y-1] != mapSide//����
			&& map[x-1][y-2] == mapSide && y-2 >=0//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x-1,y-1,-1);
			Point p3(x,y-1,1);
			Point p4(x-1,y-2,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}

		//��������=��+����+���ŵ�
		if (x - 1>=0 && y - 1>=0 && map[x-1][y-1] != 0 && map[x-1][y-1] != mapSide//��
			&& map[x-1][y] == 0//����
			&& map[x-2][y-1] == mapSide && x-2 >=0//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x-1,y-1,1);
			Point p3(x-1,y,-1);
			Point p4(x-2,y-1,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
		if (x - 1>=0 && y - 1>=0 && map[x-1][y-1] == 0 //��
			&& map[x-1][y] != 0 && map[x-1][y] != mapSide//����
			&& map[x-2][y-1] == mapSide && x-2 >=0//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x-1,y-1,-1);
			Point p3(x-1,y,1);
			Point p4(x-2,y-1,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}

		//������=����+����+���ŵ�
		if (x - 1>=0 && y + 1<=10 && map[x][y+1] != 0 && map[x][y+1] != mapSide //����
			&& map[x-1][y] == 0//����
			&& map[x-1][y+1] == mapSide//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x-1,y,-1);
			Point p3(x,y+1,1);
			Point p4(x-1,y+1,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
		if (x - 1>=0 && y + 1<=10 && map[x][y+1] == 0 //����
			&& map[x-1][y] != 0 && map[x-1][y] != mapSide//����
			&& map[x-1][y+1] == mapSide//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x-1,y,1);
			Point p3(x,y+1,-1);
			Point p4(x-1,y+1,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
		
		//��������=����+��+���ŵ�
		if (x + 1<=10 && y + 1<=10 && map[x][y+1] != 0 && map[x][y+1] != mapSide//����
			&& map[x+1][y+1] == 0//��
			&& map[x+1][y+2] == mapSide && y+2<=10//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x+1,y+1,-1);
			Point p3(x,y+1,1);
			Point p4(x+1,y+2,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
		if (x + 1<=10 && y + 1<=10 && map[x][y+1] == 0 //����
			&& map[x+1][y+1] != 0 && map[x+1][y+1] != mapSide//��
			&& map[x+1][y+2] == mapSide && y+2<=10//���ŵ�
			)
		{
			Point p1(x,y,0);
			Point p2(x+1,y+1,1);
			Point p3(x,y+1,-1);
			Point p4(x+1,y+2,0);
			VCNode[m_nVCNodeMount][0] = p1;
			VCNode[m_nVCNodeMount][1] = p2;
			VCNode[m_nVCNodeMount][2] = p3;
			VCNode[m_nVCNodeMount][3] = p4;
			m_nVCNodeMount++;
			nResultNum++;
		}
	return nResultNum;
}

void CHexView::UpdateOtherSideVCNode(int x,int y)
{
	//��������
	IsVirtualConnection(x,y,0);
	//��ʼ���°�����
	IsSemiVirtualConnection(x,y,0);
	//�޸����ż��������
		/*
		Point VCNode[N][4];//��ǰ��������Žڵ��
	int m_nVCNodeMount;
		*/
		for (int i = 0; i < m_nVCNodeMount; i++)
		{
			if( (VCNode[i][1].x == x) && (VCNode[i][1].y == y) )
			{
				VCNode[i][1].side = 0;
			}
			else if( (VCNode[i][2].x == x) && (VCNode[i][2].y == y) )
			{
				VCNode[i][2].side = 0;
			}
		}
}
