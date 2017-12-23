#include "stdafx.h"
#include "SearchEngine.h"

//辅助函数

void Go(int x, int y, int side, int depth,int (&map)[11][11],int (&IsGo)[11][11],bool IsWin)
{
	if (side == 1)
	{
		if (depth >= 10)
		{
			IsWin =  true;
			return;
		}
		//上頂點
		if ((x == 0)&&(y == 0))
		{
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth,map,IsGo,IsWin);
			}               //左下
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1,map,IsGo,IsWin);
			}
		}
		//最左點
		if ((x == 0)&&(y == 10))
		{
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth,map,IsGo,IsWin);
			}                //右上
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			
		}
		//左上邊
		if ((x == 0)&&(y > 0))
		{
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth,map,IsGo,IsWin);
			}                //右上
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth,map,IsGo,IsWin);
			}               //左下
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1,map,IsGo,IsWin);
			}              //下
		}
		//右上邊
		if ((x > 0)&&(y == 0))
		{
			
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth,map,IsGo,IsWin);
			}               //左下
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1,map,IsGo,IsWin);
			}               //下
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1,map,IsGo,IsWin);
			}//左上
		}
		//左下便
		if ((x > 0)&&(y == 10))
		{
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1,map,IsGo,IsWin);
			}//左上
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth,map,IsGo,IsWin);
			}                //右上
			if (map[x - 1][y - 1] == 1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				Go(x - 1, y - 1, side, depth - 1,map,IsGo,IsWin);
			}//上  
		}
		//中間點
		if ((x > 0)&&(y > 0))
		{
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1,map,IsGo,IsWin);
			}//左上
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth,map,IsGo,IsWin);
			}                //右上
			if (map[x - 1][y - 1] == 1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				Go(x - 1, y - 1, side, depth - 1,map,IsGo,IsWin);
			}//上  
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth,map,IsGo,IsWin);
			}               //左下
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1,map,IsGo,IsWin);
			}               //下
		}

	}
	else
	{
		if (depth >= 10)
		{
			IsWin =  true;
			return;
		}
		//上頂點
		if ((x == 0)&&(y == 0))
		{
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth,map,IsGo,IsWin);
			}               //左下
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1,map,IsGo,IsWin);
			}
		}
		//最左點
		if ((x == 0)&&(y == 10))
		{
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth,map,IsGo,IsWin);
			}                //右上
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			
		}
		//左上邊
		if ((x == 0)&&(y > 0))
		{
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth,map,IsGo,IsWin);
			}                //右上
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth,map,IsGo,IsWin);
			}               //左下
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1,map,IsGo,IsWin);
			}              //下
		}
		//右上邊
		if ((x > 0)&&(y == 0))
		{
			
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth,map,IsGo,IsWin);
			}               //左下
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1,map,IsGo,IsWin);
			}               //下
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1,map,IsGo,IsWin);
			}//左上
		}
		//左下便
		if ((x > 0)&&(y == 10))
		{
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1,map,IsGo,IsWin);
			}//左上
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth,map,IsGo,IsWin);
			}                //右上
			if (map[x - 1][y - 1] == 1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				Go(x - 1, y - 1, side, depth - 1,map,IsGo,IsWin);
			}//上  
		}
		//中間點
		if ((x > 0)&&(y > 0))
		{
			if (map[x+1][y] == 1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				Go(x+1, y, side, depth+1,map,IsGo,IsWin);
			}              //右下
			if (map[x - 1][y] == 1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				Go(x-1,y,side,depth-1,map,IsGo,IsWin);
			}//左上
			if (map[x][y - 1] == 1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				Go(x, y - 1, side, depth,map,IsGo,IsWin);
			}                //右上
			if (map[x - 1][y - 1] == 1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				Go(x - 1, y - 1, side, depth - 1,map,IsGo,IsWin);
			}//上  
			if (map[x][y + 1] == 1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				Go(x, y + 1, side, depth,map,IsGo,IsWin);
			}               //左下
			if (map[x + 1][y + 1] == 1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				Go(x + 1, y + 1, side, depth + 1,map,IsGo,IsWin);
			}               //下
		}

	}
}

bool IsBlackWin(int (&map)[11][11])               //参数含义：map的下标
{
	int IsGo[11][11];
	bool IsWin = false;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			IsGo[i][j] = -1;
		}
	}
	for (int i = 0; i < 11; i++)
	{
		if (map[0][i] == 1)
		{
			IsGo[0][i] = 1;
			Go(0, i, 1, 0,map,IsGo,IsWin);//(int x, int y, int side, int depth,int (&map)[11][11],int (&IsGo)[11][11],bool IsWin)
			for (int k = 0; k < 11; k++)                   //每次遍历完成恢复IsGo数组
			{
				for (int g = 0; g < 11; g++)
				{
					IsGo[k][g] = -1;
				}
			}
		}
	}
	return IsWin;
}

bool IsWhiteWin(int (&map)[11][11])               //参数含义：map的下标
{
	int IsGo[11][11];
	bool IsWin = false;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			IsGo[i][j] = -1;
		}
	}
	for (int i = 0; i < 11; i++)
	{
		if (map[i][0] == -1)
		{
			IsGo[i][0] = 1;
			Go(i, 0, -1, 0,map,IsGo,IsWin);
			for (int k = 0; k < 11; k++)                   //每次遍历完成恢复IsGo数组
			{
				for (int g = 0; g < 11; g++)
				{
					IsGo[k][g] = -1;
				}
			}
		}
	}
	return IsWin;
}

CSearchEngine::CSearchEngine(void)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			CurPosition[i][j] = 0;
		}
	}
	m_nCurVCNodeMount = 0;
}

CSearchEngine::~CSearchEngine(void)
{
	delete m_pEval;
	delete m_pMG;
}

void CSearchEngine::add_Node(int from,int to,int cap)
{
	CurV[from].push_back(CNode(to,cap,CurV[to].size()));  
    CurV[to].push_back(CNode(from,0,CurV[from].size()-1));  
}

bool CSearchEngine::isNewLinked(int currentNodeId,int nextNodeId)
{
	for (int i = 0; i < CurV[currentNodeId].size(); i++)
	{
		if (CurV[currentNodeId][i].to == nextNodeId)
		{
			return false;
		}
	}
	return true;
}

void CSearchEngine::UpdateSameSideNodes(int x,int y)

{
	int currentNodeId = x*11 + (y+1);
	vector<int> nextNodesId;
	vector<int> preNodesId;
	for (int i = 0; i < CurV[currentNodeId].size(); i++)
	{
		if (CurV[currentNodeId][i].to == -1)
		{
			continue;
		}
		if(CurV[currentNodeId][i].to == 0)//源点
		{
			preNodesId.push_back(0);
		}
		else if (CurV[currentNodeId][i].to == currentNodeId + 1)//左下
		{
			preNodesId.push_back(CurV[currentNodeId][i].to);  
		}
		else if ((CurV[currentNodeId][i].to > currentNodeId)||(CurV[currentNodeId][i].to == currentNodeId - 1))//右和右下 || 右上
		{
			nextNodesId.push_back(CurV[currentNodeId][i].to);  
		}
		else if (CurV[currentNodeId][i].to < currentNodeId)//上，左上
		{
			preNodesId.push_back(CurV[currentNodeId][i].to);  
		}
	}
	for (int i = 0; i < preNodesId.size(); i++)
	{
		//删去当前节点前面节点中指向删去节点的路径
		int t = preNodesId[i];
		for (int j = 0; j < CurV[t].size(); j++)
		{
			if (CurV[t][j].to == currentNodeId)
			{
				CurV[t][j].to = -1;
				CurV[t][j].cap = -1;
				CurV[t][j].rev = -1;
			}
		}
		
		
		
		//创建前面节点指向后面节点的路径
		for (int j = 0; j < nextNodesId.size(); j++)
		{
			if(isNewLinked(t,nextNodesId[j]))
				add_Node(preNodesId[i],nextNodesId[j],1);  
		}

	}
	//删去后面节点中指向当前节点的反向路径
	for (int i = 0; i < nextNodesId.size(); i++)
	{
		//删去当前节点后面节点指向删去节点的路径
		int t = nextNodesId[i];
		for (int j = 0; j < CurV[t].size(); j++)
		{
			if (CurV[t][j].to == currentNodeId)
			{
				CurV[t][j].to = -1;
				CurV[t][j].cap = -1;
				CurV[t][j].rev = -1;
			}
		}
	}

	//删去当前节点的信息
	vector<CNode> newTemp;
	CurV[currentNodeId] = newTemp;

}

void CSearchEngine::UpdateOtherSideNodes(int x,int y)
{
	int currentNodeId = x*11 + (y+1);
	vector<int> updateNodesId;
	for (int i = 0; i < CurV[currentNodeId].size(); i++)
	{
		updateNodesId.push_back(CurV[currentNodeId][i].to);  	
	}
	for (int i = 0; i < updateNodesId.size(); i++)
	{
		//删去相关节点指向删去节点的路径
		int t = updateNodesId[i];
		for (int j = 0; j < CurV[t].size(); j++)
		{
			if (CurV[t][j].to == currentNodeId)
			{
				CurV[t][j].to = -1;
				CurV[t][j].cap = -1;
				CurV[t][j].rev = -1;
			}
		}
		
	}

	//删去当前节点的信息
	vector<CNode> newTemp;
	CurV[currentNodeId] = newTemp;
	
}

void CSearchEngine::SearchAGoodMove(int (&map)[11][11],vector<CNode> (&v)[N],Point (&VCNode)[N][4],int &mount)
{
	bool IsNextSemi = false;//找下一步中有没有半虚桥
	Point nextStep;//用于下一步直接堵虚桥
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			CurPosition[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		CurV[i] = v[i];	
	}
	m_nCurVCNodeMount = mount;
	for (int i = 0; i < m_nCurVCNodeMount; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CurVCNode[i][j] = VCNode[i][j];
		}
	}
	m_nMaxDepth = m_nSearchDepth;
	//m_history.ResetHistoryTable0();
	//m_history.ResetHistoryTable1();
	//Pattern_ab_search(m_nMaxDepth,-20000,20000);
	
	//判断有无半虚桥
	for (int i = 0; i < m_nCurVCNodeMount; i++)
	{
		if ((CurVCNode[i][1].side != -1)&&(CurVCNode[i][1].side != CurVCNode[i][0].side)&&(CurVCNode[i][2].side == -1))
		{
			nextStep.x = CurVCNode[i][2].x;
			nextStep.y = CurVCNode[i][2].y;
			IsNextSemi = true;
		}
		else if ((CurVCNode[i][2].side != -1)&&(CurVCNode[i][1].side == -1)&&(CurVCNode[i][2].side != CurVCNode[i][0].side))
		{
			nextStep.x = CurVCNode[i][1].x;
			nextStep.y = CurVCNode[i][1].y;
			IsNextSemi = true;
		}
	}
	if (IsNextSemi)
	{
		m_BestMove = nextStep;
	}
	else
	{
		alpha_beta_search(m_nMaxDepth,-20000,20000);
	}
	MakeMove(m_BestMove,1);
	//memcpy(map,CurPosition,121);
	for (int i = 0; i < N; i++)
	{
		v[i] = CurV[i];
	}
	mount = m_nCurVCNodeMount;
	for (int i = 0; i < m_nCurVCNodeMount; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			VCNode[i][j] = CurVCNode[i][j];
		}
	}
}

void CSearchEngine::MakeMove(Point move,bool isBlack)
{
	m_StackCurV.Push(CurV);
	int x = move.x;
	int y = move.y;

	int mapSide;
	if (isBlack == 0)//白====
	{
		mapSide = -1;
	}
	else if (isBlack == 1)//黑
	{
		mapSide = 1;
	}


	if (isBlack == 1)
	{
		CurPosition[move.x][move.y] = 1;
		UpdateSameSideNodes(move.x,move.y);

		AddCurVCNode(move,isBlack);
		//开始更新半虚桥
		if (x + 1<=10 && CurPosition[x+1][y] != 0 && CurPosition[x+1][y] != mapSide //右下
			&& CurPosition[x+1][y+1] == 0 && y+1<=10//下
			&& CurPosition[x+2][y+1] == mapSide && x+2 <=10//虚桥点
			)//11
		{
			Point p1(x,y,1);
			Point p2(x+1,y,0);
			Point p3(x+1,y+1,-1);
			Point p4(x+2,y+1,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x + 1<=10 && CurPosition[x+1][y] == 0 //右下
			&& CurPosition[x+1][y+1] != 0 && CurPosition[x+1][y+1] != mapSide && y+1<=10//下
			&& CurPosition[x+2][y+1] == mapSide && x+2 <=10//虚桥点
			)//12
		{
			Point p1(x,y,1);
			Point p2(x+1,y,-1);
			Point p3(x+1,y+1,0);
			Point p4(x+2,y+1,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x + 1<=10 && CurPosition[x+1][y] != 0 && CurPosition[x+1][y] != mapSide//右下
			&& CurPosition[x][y-1] == 0 && y-1>=0//右上
			&& CurPosition[x+1][y-1] == mapSide//虚桥点
			)//21
		{
			Point p1(x,y,1);
			Point p2(x+1,y,0);
			Point p3(x,y-1,-1);
			Point p4(x+1,y-1,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x + 1<=10 && CurPosition[x+1][y] == 0//右下
			&& CurPosition[x][y-1] != 0 && y-1>=0 && CurPosition[x][y-1] != mapSide///右上
			&& CurPosition[x+1][y-1] == mapSide//虚桥点
			)//22
		{
			Point p1(x,y,1);
			Point p2(x+1,y,-1);
			Point p3(x,y-1,0);
			Point p4(x+1,y-1,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] != 0 && CurPosition[x-1][y-1] != mapSide //上
			&& CurPosition[x][y-1] == 0//右上
			&& CurPosition[x-1][y-2] == mapSide && y-2 >=0//虚桥点
			)//31
		{
			Point p1(x,y,1);
			Point p2(x-1,y-1,0);
			Point p3(x,y-1,-1);
			Point p4(x-1,y-2,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] ==0//上
			&& CurPosition[x][y-1] != 0 && CurPosition[x][y-1] != mapSide//右上
			&& CurPosition[x-1][y-2] == mapSide && y-2 >=0//虚桥点
			)//32
		{
			Point p1(x,y,1);
			Point p2(x-1,y-1,-1);
			Point p3(x,y-1,0);
			Point p4(x-1,y-2,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] != 0 && CurPosition[x-1][y-1] != mapSide//上
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-2][y-1] == mapSide && x-2 >=0//虚桥点
			)//41
		{
			Point p1(x,y,1);
			Point p2(x-1,y-1,0);
			Point p3(x-1,y,-1);
			Point p4(x-2,y-1,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] == 0 //上
			&& CurPosition[x-1][y] != 0 && CurPosition[x-1][y] != mapSide//左上
			&& CurPosition[x-2][y-1] == mapSide && x-2 >=0//虚桥点
			)//42
		{
			Point p1(x,y,1);
			Point p2(x-1,y-1,-1);
			Point p3(x-1,y,0);
			Point p4(x-2,y-1,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x - 1>=0 && y + 1<=10 && CurPosition[x][y+1] != 0 && CurPosition[x][y+1] != mapSide //左下
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-1][y+1] == mapSide//虚桥点
			)//51
		{
			Point p1(x,y,1);
			Point p2(x-1,y,-1);
			Point p3(x,y+1,0);
			Point p4(x-1,y+1,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x - 1>=0 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x-1][y] != 0 && CurPosition[x-1][y] != mapSide//左上
			&& CurPosition[x-1][y+1] == mapSide//虚桥点
			)//52
		{
			Point p1(x,y,1);
			Point p2(x-1,y,0);
			Point p3(x,y+1,-1);
			Point p4(x-1,y+1,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x + 1<=10 && y + 1<=10 && CurPosition[x][y+1] != 0 && CurPosition[x][y+1] != mapSide//左下
			&& CurPosition[x+1][y+1] == 0//下
			&& CurPosition[x+1][y+2] == mapSide && y+2<=10//虚桥点
			)//61
		{
			Point p1(x,y,1);
			Point p2(x+1,y+1,-1);
			Point p3(x,y+1,0);
			Point p4(x+1,y+2,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x + 1<=10 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x+1][y+1] != 0 && CurPosition[x+1][y+1] != mapSide//下
			&& CurPosition[x+1][y+2] == mapSide && y+2<=10//虚桥点
			)//62
		{
			Point p1(x,y,1);
			Point p2(x+1,y+1,0);
			Point p3(x,y+1,-1);
			Point p4(x+1,y+2,1);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		//修改虚桥间的两个点
		for (int i = 0; i < m_nCurVCNodeMount; i++)
		{
			if( (CurVCNode[i][1].x == x) && (CurVCNode[i][1].y == y) )
			{
				CurVCNode[i][1].side = 1;
			}
			else if( (CurVCNode[i][2].x == x) && (CurVCNode[i][2].y == y) )
			{
				CurVCNode[i][2].side = 1;
			}
		}
	}
	else if (isBlack == 0)
	{
		CurPosition[move.x][move.y] = -1;
		UpdateOtherSideNodes(move.x,move.y);
		AddCurVCNode(move,isBlack);
		//开始更新半虚桥
		if (x + 1<=10 && CurPosition[x+1][y] != 0 && CurPosition[x+1][y] != mapSide //右下
			&& CurPosition[x+1][y+1] == 0 && y+1<=10//下
			&& CurPosition[x+2][y+1] == mapSide && x+2 <=10//虚桥点
			)//11
		{
			Point p1(x,y,0);
			Point p2(x+1,y,1);
			Point p3(x+1,y+1,-1);
			Point p4(x+2,y+1,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x + 1<=10 && CurPosition[x+1][y] == 0 //右下
			&& CurPosition[x+1][y+1] != 0 && CurPosition[x+1][y+1] != mapSide && y+1<=10//下
			&& CurPosition[x+2][y+1] == mapSide && x+2 <=10//虚桥点
			)//12
		{
			Point p1(x,y,0);
			Point p2(x+1,y,-1);
			Point p3(x+1,y+1,1);
			Point p4(x+2,y+1,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x + 1<=10 && CurPosition[x+1][y] != 0 && CurPosition[x+1][y] != mapSide//右下
			&& CurPosition[x][y-1] == 0 && y-1>=0//右上
			&& CurPosition[x+1][y-1] == mapSide//虚桥点
			)//21
		{
			Point p1(x,y,0);
			Point p2(x+1,y,1);
			Point p3(x,y-1,-1);
			Point p4(x+1,y-1,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x + 1<=10 && CurPosition[x+1][y] == 0//右下
			&& CurPosition[x][y-1] != 0 && y-1>=0 && CurPosition[x][y-1] != mapSide///右上
			&& CurPosition[x+1][y-1] == mapSide//虚桥点
			)//22
		{
			Point p1(x,y,0);
			Point p2(x+1,y,-1);
			Point p3(x,y-1,1);
			Point p4(x+1,y-1,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] != 0 && CurPosition[x-1][y-1] != mapSide //上
			&& CurPosition[x][y-1] == 0//右上
			&& CurPosition[x-1][y-2] == mapSide && y-2 >=0//虚桥点
			)//31
		{
			Point p1(x,y,0);
			Point p2(x-1,y-1,1);
			Point p3(x,y-1,-1);
			Point p4(x-1,y-2,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] ==0//上
			&& CurPosition[x][y-1] != 0 && CurPosition[x][y-1] != mapSide//右上
			&& CurPosition[x-1][y-2] == mapSide && y-2 >=0//虚桥点
			)//32
		{
			Point p1(x,y,0);
			Point p2(x-1,y-1,-1);
			Point p3(x,y-1,1);
			Point p4(x-1,y-2,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] != 0 && CurPosition[x-1][y-1] != mapSide//上
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-2][y-1] == mapSide && x-2 >=0//虚桥点
			)//41
		{
			Point p1(x,y,0);
			Point p2(x-1,y-1,1);
			Point p3(x-1,y,-1);
			Point p4(x-2,y-1,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] == 0 //上
			&& CurPosition[x-1][y] != 0 && CurPosition[x-1][y] != mapSide//左上
			&& CurPosition[x-2][y-1] == mapSide && x-2 >=0//虚桥点
			)//42
		{
			Point p1(x,y,0);
			Point p2(x-1,y-1,-1);
			Point p3(x-1,y,1);
			Point p4(x-2,y-1,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x - 1>=0 && y + 1<=10 && CurPosition[x][y+1] != 0 && CurPosition[x][y+1] != mapSide //左下
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-1][y+1] == mapSide//虚桥点
			)//51
		{
			Point p1(x,y,0);
			Point p2(x-1,y,-1);
			Point p3(x,y+1,1);
			Point p4(x-1,y+1,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x - 1>=0 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x-1][y] != 0 && CurPosition[x-1][y] != mapSide//左上
			&& CurPosition[x-1][y+1] == mapSide//虚桥点
			)//52
		{
			Point p1(x,y,0);
			Point p2(x-1,y,1);
			Point p3(x,y+1,-1);
			Point p4(x-1,y+1,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		if (x + 1<=10 && y + 1<=10 && CurPosition[x][y+1] != 0 && CurPosition[x][y+1] != mapSide//左下
			&& CurPosition[x+1][y+1] == 0//下
			&& CurPosition[x+1][y+2] == mapSide && y+2<=10//虚桥点
			)//61
		{
			Point p1(x,y,0);
			Point p2(x+1,y+1,-1);
			Point p3(x,y+1,1);
			Point p4(x+1,y+2,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		else if (x + 1<=10 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x+1][y+1] != 0 && CurPosition[x+1][y+1] != mapSide//下
			&& CurPosition[x+1][y+2] == mapSide && y+2<=10//虚桥点
			)//62
		{
			Point p1(x,y,0);
			Point p2(x+1,y+1,1);
			Point p3(x,y+1,-1);
			Point p4(x+1,y+2,0);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		//修改虚桥间的两个点
		for (int i = 0; i < m_nCurVCNodeMount; i++)
		{
			if( (CurVCNode[i][1].x == x) && (CurVCNode[i][1].y == y) )
			{
				CurVCNode[i][1].side = 0;
			}
			else if( (CurVCNode[i][2].x == x) && (CurVCNode[i][2].y == y) )
			{
				CurVCNode[i][2].side = 0;
			}
		}

	}
	

}

void CSearchEngine::UnMakeMove(Point move,bool isBlack)
{
	CurPosition[move.x][move.y] = 0;
	vector<CNode> temp[N];
	m_StackCurV.GetTop(temp);
	for (int i = 0; i < N; i++)
	{
		CurV[i] = temp[i];
	}
	m_StackCurV.Pop();
	//更新存虚桥的数组
	Point tempVCNode[N][4];
	int n_temp = 0;
	for (int i = 0; i < m_nCurVCNodeMount; i++)
	{
		if((CurVCNode[i][0].x == move.x)&&(CurVCNode[i][0].y == move.y))
			continue;
		else if((CurVCNode[i][3].x == move.x)&&(CurVCNode[i][3].y == move.y))
			continue;
		//虚桥的中间点更新
		if( (CurVCNode[i][1].x == move.x) && (CurVCNode[i][1].y == move.y) )
		{
			CurVCNode[i][1].side = -1;
		}
		else if( (CurVCNode[i][2].x == move.x) && (CurVCNode[i][2].y == move.y) )
		{
			CurVCNode[i][2].side = -1;
		}
		tempVCNode[n_temp][0] = CurVCNode[i][0];
		tempVCNode[n_temp][1] = CurVCNode[i][1];
		tempVCNode[n_temp][2] = CurVCNode[i][2];
		tempVCNode[n_temp][3] = CurVCNode[i][3];
		n_temp++;
	}
	m_nCurVCNodeMount = 0;
	for (int i = 0; i < n_temp; i++)
	{
		CurVCNode[m_nCurVCNodeMount][0] = tempVCNode[i][0];
		CurVCNode[m_nCurVCNodeMount][1] = tempVCNode[i][1];
		CurVCNode[m_nCurVCNodeMount][2] = tempVCNode[i][2];
		CurVCNode[m_nCurVCNodeMount][3] = tempVCNode[i][3];
		m_nCurVCNodeMount++;
	}

}
	
int CSearchEngine::IsGameOver(int (&map)[11][11],int nDepth)
{
	int i = (m_nMaxDepth - nDepth + 1) % 2;
	if (IsWhiteWin(map))
	{
		if (i == 1) return 19990;
		else return -19990;
	}
	if (IsBlackWin(map))//黑棋赢了  先下的赢了
	{
		if (i == 1) return -19990;
		else return 19990;
	}
	return 0;
}

CPattern CSearchEngine::Pattern_ab_search(int depth,int alpha,int beta)
{
	//初始化win和lose的值
	int tt = (m_nMaxDepth - depth + 1) % 2;
	int win,lose;
	int side = (m_nMaxDepth - depth)%2;
	if (side == 0)//白
	{
		if (tt == 1) win = 19990;
		else win = -19990;
	}
	if (side == 1)//黑棋赢了  先下的赢了
	{
		if (tt == 1) win = -19990;
		else win = 19990;
	}
	lose = -win;
	//////////////////


	CPattern result;
	int i,count;
	i = IsGameOver(CurPosition,depth);
	if (i == 19990)
	{
		result.paToVoid();
		result.value = i;
		return result;
	}
	
	if (depth <= 0)
	{
		result.paToVoid();
		result.value = m_pEval->Eveluate(CurV,(m_nMaxDepth - depth)%2);
		return result;
	}

	result.paToVoid();
	//result.value = lose;
	result.value = 0;
	count = m_pMG->CreatePossibleMove(CurVCNode,m_nCurVCNodeMount,CurPosition,depth,(m_nMaxDepth - depth)%2);

	for (i = 0; i < count; i++)
	{
		if ((m_pMG->m_MoveList[depth][i].x == -1) || (m_pMG->m_MoveList[depth][i].y == -1))
		{
			continue;
		}
		MakeMove(m_pMG->m_MoveList[depth][i],(m_nMaxDepth - depth)%2);
		CPattern temp = Pattern_ab_search(depth - 1, -beta, -alpha);
		UnMakeMove(m_pMG->m_MoveList[depth][i],(m_nMaxDepth - depth)%2);
		if (result.value == lose)
		{
			result.value = win;
			temp.pa[m_pMG->m_MoveList[depth][i].x][m_pMG->m_MoveList[depth][i].y] = true;
			//memcpy(result.pa,temp.pa,121);
			for (int j = 0; j < 11; j++)
				for (int k = 0; k < 11; k++)
				{
					result.pa[j][k] = temp.pa[j][k];
				}
			return result;
		}
		else if (result.value == win)
		{
			for (int j = 0; j < 11; j++)
				for (int k = 0; k < 11; k++)
				{
					if (temp.pa[j][k] == true)
					{
						result.pa[j][k] = true;
					}
				}
			for (int j = i+1; j < count; j++)
			{
				int tx = m_pMG->m_MoveList[depth][j].x;
				int ty = m_pMG->m_MoveList[depth][j].y;
				if(temp.pa[tx][ty] == false)
				{
					m_pMG->m_MoveList[depth][j].x = -1;
					m_pMG->m_MoveList[depth][j].y = -1;
				}
			}
		}

		result.value = max(result.value,temp.value);
		if (result.value > alpha)
		{
			alpha = result.value;
			if (depth == m_nMaxDepth)
			{
				m_BestMove = m_pMG->m_MoveList[depth][i];
			}
		}
		if (result.value >= beta) return result;

	}
	return result;
}

int CSearchEngine::alpha_beta_search(int depth,int alpha,int beta)
{
	int score;
	int i,count,flag,side;
	side = (m_nMaxDepth - depth)%2;
	i = IsGameOver(CurPosition,depth);
	if (i != 0)	return i;
	
	score = LookUpHashTable(alpha,beta,depth,side);

	if (depth <= 0) 
	{
		score = m_pEval->Eveluate(CurV,side);
		EnterHashTable(exact,score,depth,side);
		return score;
	}

	count = m_pMG->CreatePossibleMove(CurVCNode,m_nCurVCNodeMount,CurPosition,depth,side);
	int eval_is_exact = 0;
	flag = side;

	//排序
	/*
	if (flag == 0)
	{
		m_history.PopSort0(m_pMG->m_MoveList[depth],count);
	}
	else if(flag == 1)
	{
		m_history.PopSort1(m_pMG->m_MoveList[depth],count);
	}*/
	int bestmove = -1;

	for (i = 0; i < count; i++)
	{
		MakeMove(m_pMG->m_AllMoveList[depth][i],side);
		Hash_MakeMove(m_pMG->m_AllMoveList[depth][i],CurPosition);
		score = -alpha_beta_search(depth - 1,-beta,-alpha);
		Hash_UnMakeMove(m_pMG->m_AllMoveList[depth][i],CurPosition);
		UnMakeMove(m_pMG->m_AllMoveList[depth][i],side);
		if (score >= beta)
		{
			EnterHashTable(lower_bound,score,depth,side);
			return score;
		}
		if (score > alpha)
		{
			alpha = score;
			eval_is_exact = 1;
			if (depth == m_nMaxDepth)
			{
				m_BestMove = m_pMG->m_AllMoveList[depth][i];
			}
			bestmove = i;
		}
			if (alpha >= beta) 
			{
				bestmove = i;
				break;
			}
	}
	/*
	if (bestmove != -1)
	{
		if (flag == 0)
		{
			m_history.EnterHistoryScore0(m_pMG->m_MoveList[depth][bestmove],depth);
		}
		else if (flag == 1)
		{
			m_history.EnterHistoryScore1(m_pMG->m_MoveList[depth][bestmove],depth);
		}
	}*/
	if(eval_is_exact) 
		EnterHashTable(exact,alpha,depth,side);
	else 
		EnterHashTable(upper_bound,alpha,depth,side);

	return alpha;
}

void CSearchEngine::AddCurVCNode(Point move,bool isBlack)
{
	int x = move.x;
	int y = move.y;
	int mapSide;
	if (isBlack == 0)//白====
	{
		mapSide = -1;
	}
	else if (isBlack == 1)//黑
	{
		mapSide = 1;
	}
	//右下虚桥=右下+下+虚桥点
		if (x + 1<=10 && CurPosition[x+1][y] == 0 //右下
			&& CurPosition[x+1][y+1] == 0 && y+1<=10//下
			&& CurPosition[x+2][y+1] == mapSide && x+2 <=10//虚桥点
			)//1
		{
			Point p1(move.x,move.y,isBlack);
			Point p2(x+1,y,-1);
			Point p3(x+1,y+1,-1);
			Point p4(x+2,y+1,isBlack);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		//右虚桥=右下+右上+虚桥点
		if (x + 1<=10 && CurPosition[x+1][y] == 0 //右下
			&& CurPosition[x][y-1] == 0 && y-1>=0//右上
			&& CurPosition[x+1][y-1] == mapSide//虚桥点
			)//2
		{
			Point p1(move.x,move.y,isBlack);
			Point p2(x+1,y,-1);
			Point p3(x,y-1,-1);
			Point p4(x+1,y-1,isBlack);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		//右上虚桥=上+右上+虚桥点
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] == 0 //上
			&& CurPosition[x][y-1] == 0//右上
			&& CurPosition[x-1][y-2] == mapSide && y-2 >=0//虚桥点
			)//3
		{
			Point p1(move.x,move.y,isBlack);
			Point p2(x-1,y-1,-1);
			Point p3(x,y-1,-1);
			Point p4(x-1,y-2,isBlack);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		//左上虚桥=上+左上+虚桥点
		if (x - 1>=0 && y - 1>=0 && CurPosition[x-1][y-1] == 0 //上
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-2][y-1] == mapSide && x-2 >=0//虚桥点
			)//4
		{
			Point p1(move.x,move.y,isBlack);
			Point p2(x-1,y-1,-1);
			Point p3(x-1,y,-1);
			Point p4(x-2,y-1,isBlack);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		//左虚桥=左下+左上+虚桥点
		if (x - 1>=0 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x-1][y] == 0//左上
			&& CurPosition[x-1][y+1] == mapSide//虚桥点
			)//5
		{
			Point p1(move.x,move.y,isBlack);
			Point p2(x-1,y,-1);
			Point p3(x,y+1,-1);
			Point p4(x-1,y+1,isBlack);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
		//左下虚桥=左下+下+虚桥点
		if (x + 1<=10 && y + 1<=10 && CurPosition[x][y+1] == 0 //左下
			&& CurPosition[x+1][y+1] == 0//下
			&& CurPosition[x+1][y+2] == mapSide && y+2<=10//虚桥点
			)//6
		{
			Point p1(move.x,move.y,isBlack);
			Point p2(x+1,y+1,-1);
			Point p3(x,y+1,-1);
			Point p4(x+1,y+2,isBlack);
			CurVCNode[m_nCurVCNodeMount][0] = p1;
			CurVCNode[m_nCurVCNodeMount][1] = p2;
			CurVCNode[m_nCurVCNodeMount][2] = p3;
			CurVCNode[m_nCurVCNodeMount][3] = p4;
			m_nCurVCNodeMount++;
		}
}