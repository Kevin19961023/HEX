#include "stdafx.h"
#include "Eveluation.h"

#define INF 0x3f3f3f3f

CEveluation::CEveluation(void)
{
	value = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			IsGo[i][j] = -1;                                       //1--走过   -1----没走过
		}
	}
}


CEveluation::~CEveluation(void)
{
}
/*
void CEveluation::Go(int map[11][11],int x,int y,int side,int depth)
{
	if (side == 1)
	{
		if (depth >= 10)
		{
			value += path.Sum();
			//path.Pop();
			return;
		}
		//上顶点
		if ((x == 0)&&(y == 0))
		{
			if (map[x][y + 1] != -1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				path.Push(map[x][y + 1]);
				Go(map,x, y + 1, side, depth);
				path.Pop();
				IsGo[x][y + 1] = -1;
			}               //左下
			if (map[x + 1][y] != -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				path.Push(map[x + 1][y]);
				Go(map,x+1, y, side, depth+1);
				path.Pop();
				IsGo[x+1][y] = -1;
			}              //右下
			if (map[x + 1][y + 1] != -1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				path.Push(map[x + 1][y + 1]);
				Go(map,x + 1, y + 1, side, depth + 1);
				path.Pop();
				IsGo[x + 1][y + 1] = -1;
			}
		}
		//最左點
		if ((x == 0)&&(y == 10))
		{
			if (map[x][y - 1] != -1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				path.Push(map[x][y - 1]);
				Go(map,x, y - 1, side, depth);
				path.Pop();
				IsGo[x][y - 1] = -1;
			}                //右上
			if (map[x+1][y] != -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				path.Push(map[x+1][y]);
				Go(map,x+1, y, side, depth+1);
				path.Pop();
				IsGo[x+1][y] = -1;
			}              //右下
			
		}
		//左上邊
		if ((x == 0)&&(y > 0))
		{
			if (map[x][y - 1] != -1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				path.Push(map[x][y - 1]);
				Go(map,x, y - 1, side, depth);
				path.Pop();
				IsGo[x][y - 1] = -1;
			}                //右上
			if (map[x+1][y] != -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				path.Push(map[x+1][y]);
				Go(map,x+1, y, side, depth+1);
				path.Pop();
				IsGo[x+1][y] = -1;
			}              //右下
			if (map[x][y + 1] != -1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				path.Push(map[x][y + 1]);
				Go(map,x, y + 1, side, depth);
				path.Pop();
				IsGo[x][y + 1] = -1;
			}               //左下
			if (map[x + 1][y + 1] != -1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				path.Push(map[x+1][y + 1]);
				Go(map,x + 1, y + 1, side, depth + 1);
				path.Pop();
				IsGo[x + 1][y + 1] = -1;
			}              //下
		}
		//右上邊
		if ((x > 0)&&(y == 0))
		{
			
			if (map[x+1][y] != -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				path.Push(map[x+1][y]);
				Go(map,x+1, y, side, depth+1);
				path.Pop();
				IsGo[x+1][y] = -1;
			}              //右下
			if (map[x][y + 1] != -1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				path.Push(map[x][y + 1]);
				Go(map,x, y + 1, side, depth);
				path.Pop();
				IsGo[x][y + 1] = -1;
			}               //左下
			if (map[x + 1][y + 1] != -1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				path.Push(map[x + 1][y + 1]);
				Go(map,x + 1, y + 1, side, depth + 1);
				path.Pop();
				IsGo[x + 1][y + 1] = -1;
			}               //下
			if (map[x - 1][y] != -1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				path.Push(map[x - 1][y]);
				Go(map,x-1,y,side,depth-1);
				path.Pop();
				IsGo[x-1][y] = -1;
			}//左上
		}
		//左下便
		if ((x > 0)&&(y == 10))
		{
			if (map[x+1][y] != -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				path.Push(map[x+1][y]);
				Go(map,x+1, y, side, depth+1);
				path.Pop();
				IsGo[x+1][y] = -1;
			}              //右下
			if (map[x - 1][y] != -1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				path.Push(map[x - 1][y]);
				Go(map,x-1,y,side,depth-1);
				path.Pop();
				IsGo[x-1][y] = -1;
			}//左上
			if (map[x][y - 1] != -1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				path.Push(map[x][y - 1]);
				Go(map,x, y - 1, side, depth);
				path.Pop();
				IsGo[x-1][y] = -1;
			}                //右上
			if (map[x - 1][y - 1] != -1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				path.Push(map[x - 1][y - 1]);
				Go(map,x - 1, y - 1, side, depth - 1);
				path.Pop();
				IsGo[x - 1][y - 1] = -1;
			}//上  
		}
		//中間點
		if ((x > 0)&&(y > 0))
		{
			if (map[x+1][y] != -1 && IsGo[x+1][y] == -1)
			{
				IsGo[x+1][y] = 1;
				path.Push(map[x+1][y]);
				Go(map,x+1, y, side, depth+1);
				path.Pop();
				IsGo[x+1][y] = -1;
			}              //右下
			if (map[x - 1][y] != -1 && IsGo[x-1][y] == -1)
			{
				IsGo[x-1][y] = 1;
				path.Push(map[x - 1][y]);
				Go(map,x-1,y,side,depth-1);
				path.Pop();
				IsGo[x-1][y] = -1;
			}//左上
			if (map[x][y - 1] != -1 && IsGo[x][y - 1] == -1)
			{
				IsGo[x][y - 1] = 1;
				path.Push(map[x][y - 1]);
				Go(map,x, y - 1, side, depth);
				path.Pop();
				IsGo[x][y - 1] = -1;
			}                //右上
			if (map[x - 1][y - 1] != -1 && IsGo[x - 1][y - 1] == -1)
			{
				IsGo[x - 1][y - 1] = 1;
				path.Push(map[x - 1][y - 1]);
				Go(map,x - 1, y - 1, side, depth - 1);
				path.Pop();
				IsGo[x - 1][y - 1] = -1;
			}//上  
			if (map[x][y + 1] != -1 && IsGo[x][y + 1] == -1)
			{
				IsGo[x][y + 1] = 1;
				path.Push(map[x][y + 1]);
				Go(map,x, y + 1, side, depth);
				path.Pop();
				IsGo[x][y + 1] = -1;
			}               //左下
			if (map[x + 1][y + 1] != -1 && IsGo[x + 1][y + 1] == -1)
			{
				IsGo[x + 1][y + 1] = 1;
				path.Push(map[x + 1][y + 1]);
				Go(map,x + 1, y + 1, side, depth + 1);
				path.Pop();
				IsGo[x + 1][y + 1] = -1;
			}               //下
		}
		

	}
	else
	{
		
	}
}
*/
int CEveluation::Eveluate(int (&map)[11][11],vector<CNode> (&v)[N])
{
	return max_flow(0,122,v);
}

int CEveluation::Eveluate(vector<CNode> (&v)[N],bool bIsBlackTurn)
{
	return max_flow(0,122,v);
}

int CEveluation::dfs(int s,int t,int f,vector<CNode> (&v)[N])  
{  
    if(s>=t)  
        return f;  
    used[s]=true;  
    for(int i=0;i<v[s].size();i++)  
    {  
        CNode &tmp = v[s][i];  //注意  
        if(used[tmp.to]==false && tmp.cap>0)  
        {  
            int d=dfs(tmp.to,t,min(f,tmp.cap),v);  
            if(d>0)  
            {  
                tmp.cap-=d;  
                v[tmp.to][tmp.rev].cap+=d;  
                return d;  
            }  
        }  
    }  
    return 0;  
}  
  
int CEveluation::max_flow(int s,int t,vector<CNode> (&v)[N])  
{  
    int flow=0;  
    for(;;){  
        memset(used,false,sizeof(used));  
        int f=dfs(s,t,INF,v);  
        if(f==0)  
            return flow;  
        flow+=f;  
    }  
}  