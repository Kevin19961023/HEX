#pragma once

#define MAX 2000
#define N 123
#include <vector> 
#include "Node.h"
using namespace std; 

class CStack
{
public:
	vector<CNode> data[MAX][N];
	int top;
	int size;
	CStack(void);
	~CStack(void);

	void GetTop(vector<CNode> (&v)[N]);
	bool Pop();
	bool Push(vector<CNode> (&v)[N]);
};

