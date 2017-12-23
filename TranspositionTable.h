#pragma once
#include "Point.h"


//定义了枚举型的数据类型，精确，下边界，上边界
enum ENTRY_TYPE{exact,lower_bound,upper_bound};

//哈希表中元素的结构定义
typedef struct HASHITEM
{
	LONGLONG checksum;	  //64位校验码
	ENTRY_TYPE entry_type;//数据类型
	short depth;		  //取得此值时的层次
	short eval;			  //节点的值
}HashItem;


class CTranspositionTable
{
public:
	CTranspositionTable(void);
	~CTranspositionTable(void);
public:
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth,int TableNo);
																     //将当前节点的值存入哈希表
	int LookUpHashTable(int alpha, int beta, int depth,int TableNo); //查询哈希表中当前节点数据
	void Hash_UnMakeMove(Point move,int (&CurPosition)[11][11]);  
																	 //撤销所给走法的哈希值，还原成走过之前的
	void Hash_MakeMove(Point move,int (&CurPosition)[11][11]);//根据所给走法，增量生成新的哈希值
	void CalculateInitHashKey(int (&CurPosition)[11][11]);		 //计算给定棋盘的哈希值
	void InitializeHashKey();

	UINT m_nHashKey32[15][11][11];	   //32位随机树组，用以生成32位哈希值
	ULONGLONG m_ulHashKey64[15][11][11];//64位随机树组，用以生成64位哈希值
	HashItem *m_pTT[3];			   //置换表头指针
	UINT m_HashKey32;				   //32位哈希值
	LONGLONG m_HashKey64;			   //64 位哈希值
};

