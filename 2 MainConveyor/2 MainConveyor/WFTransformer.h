#pragma once

#include "stdafx.h"
#include "waveFunction.h"
#include "Operators.h"
#include "pairOperators.h"
#include "MyFunctions.h"
class WFTransformer
{
	
	std::vector<inter> interactions[N];
	std::vector<extendedInter> extInteractions[N];

public:

	Operators vOperator;
	pairOperators pairOperator;
	WFTransformer();
	~WFTransformer();
	
	void clear();
	void returnV(int edgeNum, int nodeNumsOfEdges[][2], std::vector<edge> edges);
	void setInteractions(int nodeNumsOfEdges[][2], std::vector<edge> edges);
	void actCopy(WaveFunction& inWF, WaveFunction& outWF);
	void act(WaveFunction& inWF, WaveFunction& outWF, int interNumber,int type,int power);

	void actPairMatrix(WaveFunction& inWF, WaveFunction& outWF, int interNumber, int type, int power);

	void actInside(WaveFunction& inWF, WaveFunction& outWF, int interNumber,int type, int power);
};

