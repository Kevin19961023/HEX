#pragma once


#include <vector> 
using namespace std;

class CNode
{
public:
	int to;//终点  
    int cap; //容量  
    int rev;  //反向边  
	CNode(int a,int b,int c);
	~CNode(void);
};

