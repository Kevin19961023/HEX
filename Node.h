#pragma once


#include <vector> 
using namespace std;

class CNode
{
public:
	int to;//�յ�  
    int cap; //����  
    int rev;  //�����  
	CNode(int a,int b,int c);
	~CNode(void);
};

