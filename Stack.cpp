#include "stdafx.h"
#include "Stack.h"


CStack::CStack(void)
{
	top = -1;
	size = MAX;
}


CStack::~CStack(void)
{
}

void CStack::GetTop(vector<CNode> (&v)[N])
{
	for (int i = 0; i < N; i++)
	{
		v[i] = data[top][i];
	}
}

bool CStack::Pop()
{
	if (top == 0)
	{
		return false;
	}
	top--;
	return true;
}
	
bool CStack::Push(vector<CNode> (&v)[N])
{
	top++;
	for (int i = 0; i < N; i++)
	{
		data[top][i] = v[i];
	}
	return true;
}
