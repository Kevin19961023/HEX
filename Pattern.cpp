#include "stdafx.h"
#include "Pattern.h"


CPattern::CPattern(void)
{
}


CPattern::~CPattern(void)
{
}

void CPattern::paToVoid()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			pa[i][j] = false;
		}
	}
}