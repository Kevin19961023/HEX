#include "stdafx.h"
#include "Node.h"


CNode::CNode(int a,int b,int c)
{
	to = a;//终点  
    cap = b; //容量  
    rev = c;  //反向边  
}

CNode::~CNode(void)
{
}
