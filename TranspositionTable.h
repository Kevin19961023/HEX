#pragma once
#include "Point.h"


//������ö���͵��������ͣ���ȷ���±߽磬�ϱ߽�
enum ENTRY_TYPE{exact,lower_bound,upper_bound};

//��ϣ����Ԫ�صĽṹ����
typedef struct HASHITEM
{
	LONGLONG checksum;	  //64λУ����
	ENTRY_TYPE entry_type;//��������
	short depth;		  //ȡ�ô�ֵʱ�Ĳ��
	short eval;			  //�ڵ��ֵ
}HashItem;


class CTranspositionTable
{
public:
	CTranspositionTable(void);
	~CTranspositionTable(void);
public:
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth,int TableNo);
																     //����ǰ�ڵ��ֵ�����ϣ��
	int LookUpHashTable(int alpha, int beta, int depth,int TableNo); //��ѯ��ϣ���е�ǰ�ڵ�����
	void Hash_UnMakeMove(Point move,int (&CurPosition)[11][11]);  
																	 //���������߷��Ĺ�ϣֵ����ԭ���߹�֮ǰ��
	void Hash_MakeMove(Point move,int (&CurPosition)[11][11]);//���������߷������������µĹ�ϣֵ
	void CalculateInitHashKey(int (&CurPosition)[11][11]);		 //����������̵Ĺ�ϣֵ
	void InitializeHashKey();

	UINT m_nHashKey32[15][11][11];	   //32λ������飬��������32λ��ϣֵ
	ULONGLONG m_ulHashKey64[15][11][11];//64λ������飬��������64λ��ϣֵ
	HashItem *m_pTT[3];			   //�û���ͷָ��
	UINT m_HashKey32;				   //32λ��ϣֵ
	LONGLONG m_HashKey64;			   //64 λ��ϣֵ
};

