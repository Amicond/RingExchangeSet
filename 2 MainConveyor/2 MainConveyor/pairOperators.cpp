#include "stdafx.h"
#include "pairOperators.h"


int pairOperators::statesToRow(int s1, int s2, bool inverseOrder = false)
{
	if (!inverseOrder)
		return s1*DiffStates + s2;
	else
		return s2*DiffStates + s1;
}

void pairOperators::ColumnToStates(int column, int &s1, int &s2, bool inverseOrder = false)
{
	if (!inverseOrder)
	{
		s1 = column / DiffStates;
		s2 = column%DiffStates;
	}
	else
	{
		s2 = column / DiffStates;
		s1 = column%DiffStates;
	}
}

pairOperators::pairOperators()
{
}


pairOperators::~pairOperators()
{
}
