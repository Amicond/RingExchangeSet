#pragma once

#include "stdafx.h"
#include "waveFunction.h"
#include "Operators.h"
#include "pairOperators.h"
#include "MyFunctions.h"
#include "RouteOperator.h"
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

	//sequential acting set
	void returnV(int edgeNum, int nodeNumsOfEdges[][2], std::vector<edge> edges);
	void setInteractions(int nodeNumsOfEdges[][2], std::vector<edge> edges);
	void actCopy(WaveFunction& inWF, WaveFunction& outWF);
	void act(WaveFunction& inWF, WaveFunction& outWF, int interNumber,int type,int power);
	void actInside(WaveFunction& inWF, WaveFunction& outWF, int interNumber,int type, int power);


	//pairMatrix set of functions
	
	void WFTransformer::returnPairVOperator(int operatorNum, int nodeNumsOfEdge, std::vector<RouteOperator> operators);
	//void setPairInteractions(int nodeNumsOfEdges[][2], std::vector<edge> edges);
	//void actCopy(WaveFunction& inWF, WaveFunction& outWF); same as in 
	void actPairMatrix(WaveFunction& inWF, WaveFunction& outWF, int interNumber, int type, int power);

};

