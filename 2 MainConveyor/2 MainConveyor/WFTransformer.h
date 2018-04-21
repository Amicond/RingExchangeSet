#ifndef __WF_TRANSFORMER_H__
#define __WF_TRANSFORMER_H__



#include "stdafx.h"
#include "waveFunction.h"
#include "Operators.h"
#include "pairOperators.h"
#include "MyFunctions.h"
#include "RouteOperator.h"
#include "ExtendedRoute.h"

class WFTransformer
{
	
	std::vector<inter> interactions[N];
	std::vector<ExtendedInter> extendedInteractions;

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
	
	void returnPairVOperator(ExtendedInter &curExtendedInter, RouteOperator &curOperator, std::vector<Point> curRoutePoints);
	void setExtendedInteractions(ExtendedRoute curRoute);
	
	//void setPairInteractions(int nodeNumsOfEdges[][2], std::vector<edge> edges);
	//void actCopy(WaveFunction& inWF, WaveFunction& outWF); same as in 
	void actPairMatrix(WaveFunction& inWF, WaveFunction& outWF, int interNumber, int type, int power);
	void actPairInside(WaveFunction& inWF, WaveFunction& outWF, int plaquetNumber, int type, int power);

};

#endif // !__WF_TRANSFORMER_H__

