#pragma once

#define N 123

#include "Stack.h"
#include "Node.h"
#include <vector> 
using namespace std; 


class CEveluation
{
public:
	int IsGo[11][11];
	float value;
	CStack path;
	bool used[N];
	void Go(int (&map)[11][11],int x,int y,int side,int depth);
	int Eveluate(int (&map)[11][11],vector<CNode> (&v)[N]);
	int Eveluate(vector<CNode> (&v)[N],bool bIsBlackTurn);
	int dfs(int s,int t,int f,vector<CNode> (&v)[N]);
	int max_flow(int s,int t,vector<CNode> (&v)[N]);
	CEveluation(void);
	~CEveluation(void);
	
};

