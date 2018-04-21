#include "stdafx.h"
#include "WFTransformer.h"




WFTransformer::WFTransformer()
{

}


WFTransformer::~WFTransformer()
{
}

void WFTransformer::clear()
{
	for (int i = 0; i < N; i++)
	{
		interactions[i].clear();
	}
	extendedInteractions.clear();
}


void WFTransformer::returnV(int edgeNum, int nodeNumsOfEdges[][2], std::vector<edge> edges)
{
	int dx = edges[edgeNum].x2 - edges[edgeNum].x1;
	int dy = edges[edgeNum].y2 - edges[edgeNum].y1;
	int n1 = nodeNumsOfEdges[edgeNum][0];
	int n2 = nodeNumsOfEdges[edgeNum][1];
	inter curInteraction;
	
	if ((dx == 1) && (dy == 0))// по горизонтали направо
	{
		curInteraction.Jtype = 0;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 1;  curInteraction.v2 = 0;
		interactions[edgeNum].push_back(curInteraction);

		
		curInteraction.Jtype = 0;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 2;  curInteraction.v2 = 3;
		interactions[edgeNum].push_back(curInteraction);

		
		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 1;  curInteraction.v2 = 3;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 2;  curInteraction.v2 = 0;
		interactions[edgeNum].push_back(curInteraction);
	}
	if ((dx == 1) && (dy == 1)) //по диагонали вправо вверх
	{		
		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 1;  curInteraction.v2 = 3;
		interactions[edgeNum].push_back(curInteraction);
	}

	if ((dx == 0) && (dy == 1))//строго вверх
	{
		curInteraction.Jtype = 0;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 0;  curInteraction.v2 = 3;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 0;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 1;  curInteraction.v2 = 2;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 0;  curInteraction.v2 = 2;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 1;  curInteraction.v2 = 3;
		interactions[edgeNum].push_back(curInteraction);
	}
	if ((dx == -1) && (dy == 1)) //по диагонали влево вверх
	{
		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 0;  curInteraction.v2 = 2;
		interactions[edgeNum].push_back(curInteraction);
	}//ок
	if ((dx == -1) && (dy == 0))//строго влево
	{
		curInteraction.Jtype = 0;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 0;  curInteraction.v2 = 1;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 0;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 3;  curInteraction.v2 = 2;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 0;  curInteraction.v2 = 2;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 3;  curInteraction.v2 = 1;
		interactions[edgeNum].push_back(curInteraction);
	}//ок
	if ((dx == -1) && (dy == -1)) //по диагонали влево вниз
	{
		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 3;  curInteraction.v2 = 1;
		interactions[edgeNum].push_back(curInteraction);
	}//ок
	if ((dx == 0) && (dy == -1))//строго вниз
	{
		curInteraction.Jtype = 0;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 2;  curInteraction.v2 = 1;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 0;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 3;  curInteraction.v2 = 0;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 2;  curInteraction.v2 = 0;
		interactions[edgeNum].push_back(curInteraction);

		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 3;  curInteraction.v2 = 1;
		interactions[edgeNum].push_back(curInteraction);
	}//ок

	if ((dx == 1) && (dy == -1)) //по диагонали нараво вниз
	{
		curInteraction.Jtype = 1;
		curInteraction.n1 = n1; curInteraction.n2 = n2;
		curInteraction.v1 = 2;  curInteraction.v2 = 0;
		interactions[edgeNum].push_back(curInteraction);
	}//ок
}

void WFTransformer::returnPairVOperator(ExtendedInter &curExtendedInter,RouteOperator &curOperator, std::vector<Point> curRoutePoints)
{

	auto curOperatorPoints = curOperator.getPoints();
	if (curOperator.getType() < 2)//pair operator case
	{
		curExtendedInter.plaquetsAmount = 2;
		curExtendedInter.Jtype[0] = 0; //first should be J-matrix. Order of matrix declared in pairMatrixNames array in "pairOperators.cpp". Factor names in "JFactor.cpp"
		curExtendedInter.Jtype[1] = 1; //second- Q-matrix. Order of matrix declared in pairMatrixNames array in "pairOperators.cpp". Factor names in "JFactor.cpp"
		
		//vertical case
		if (curOperatorPoints[0].getX() == curOperatorPoints[1].getX())
		{
			curExtendedInter.operatorType[0] = 1; //Jvert-matrix. Order by "pairOperators.cpp"
			curExtendedInter.operatorType[1] = 3; //Qvert-matrix. Order by "pairOperators.cpp"
			if (curOperatorPoints[0].getY() <= curOperatorPoints[1].getY())
			{
				curExtendedInter.n[0] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), curOperatorPoints[1]));
				curExtendedInter.n[1] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), curOperatorPoints[0]));
			}
			else
			{
				curExtendedInter.n[0] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), curOperatorPoints[0]));
				curExtendedInter.n[1] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), curOperatorPoints[1]));
			}
		}
		//horisontal case
		else if(curOperatorPoints[0].getY() == curOperatorPoints[1].getY())
		{
			curExtendedInter.operatorType[0] = 0; //Jvert-matrix. Order by "pairOperators.cpp"
			curExtendedInter.operatorType[1] = 2; //Qvert-matrix. Order by "pairOperators.cpp"
			if (curOperatorPoints[0].getX() <= curOperatorPoints[1].getX())
			{
				curExtendedInter.n[0] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), curOperatorPoints[0]));
				curExtendedInter.n[1] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), curOperatorPoints[1]));
			}
			else
			{
				curExtendedInter.n[0] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), curOperatorPoints[1]));
				curExtendedInter.n[1] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), curOperatorPoints[0]));
			}
		}
		else
		{
			std::cout << "\n\n\nError opertor convertion in \"returnPairVOpertator\" from WFTTransformer!!\n\n\n";
		}
	}
	//quatro case
	else
	{
		int maxX = std::max(std::max(curOperatorPoints[0].getX(), curOperatorPoints[1].getX()), curOperatorPoints[2].getX()); //any 3 points of 4 are enough to find top-right
		int maxY = std::max(std::max(curOperatorPoints[0].getY(), curOperatorPoints[1].getY()), curOperatorPoints[2].getY()); //any 3 points of 4 are enough to find top-right
		curExtendedInter.n[0] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), Point(maxX - 1, maxY)));   //top-left
		curExtendedInter.n[1] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), Point(maxX, maxY)));	   //top-right
		curExtendedInter.n[2] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), Point(maxX - 1, maxY-1))); //bottom-left
		curExtendedInter.n[3] = distance(curRoutePoints.begin(), find(curRoutePoints.begin(), curRoutePoints.end(), Point(maxX, maxY-1)));	   //bottom-right
		curExtendedInter.plaquetsAmount = 4;
		curExtendedInter.operatorType[0] = 4; //Qhor1 Order by "pairOperators.cpp"
		curExtendedInter.operatorType[1] = 5; //Qhor2 Order by "pairOperators.cpp"
		curExtendedInter.operatorType[2] = 6; //Qvert1 Order by "pairOperators.cpp"
		curExtendedInter.operatorType[3] = 7; //Qvert2 Order by "pairOperators.cpp"
		curExtendedInter.Jtype[0] = -1;  //Doesn't add additional factor
		curExtendedInter.Jtype[1] = 1;   //Q-factor. Order of matrix declared in pairMatrixNames array in "pairOperators.cpp". Factor names in "JFactor.cpp"
										 //using in actPair
		curExtendedInter.Jtype[2] = -1;  //Doesn't add additional factor
		curExtendedInter.Jtype[3] = 1;
	}

	return;
}

void WFTransformer::setInteractions(int nodeNumsOfEdges[][2],std::vector<edge> edges)
{
	int edgeAmount = edges.size();
	for (int number = 0; number < edgeAmount; number++)
	{
		returnV(number, nodeNumsOfEdges, edges);
	}
}

void WFTransformer::setExtendedInteractions(ExtendedRoute curRoute)
{
	std::vector<Point> curRoutePoints;
	curRoute.getSize();
	curRoute.evaluateRouteProperties(curRoutePoints);
	ExtendedInter curExtInteraction;
	for (int i = 0; i < curRoute.getSize(); i++)
	{
		returnPairVOperator(curExtInteraction,curRoute.operators[i], curRoutePoints);
		extendedInteractions.push_back(curExtInteraction);
	}
}

void WFTransformer::actCopy(WaveFunction& inWF, WaveFunction& outWF)
{
	for (int i = 0; i < inWF.getEigenstatesAmount(); i++)
		outWF.addEigenState(inWF.getEigenstateByNumber(i));
}

void WFTransformer::act(WaveFunction& inWF, WaveFunction& outWF, int interNumber,int type,int power) 
//type: 0 excitation states, pure factor
//type: 1 ground states, pure factor
//type: 2 excitation states, factor is divided by energy in first power
//type: 3 excitation states, factor is divided by energy in first power

{
	State currentInputState;//const state from 
	//temp
	int nodesAmout = inWF.getNodesAmount();
	//temp end
	State tempst(nodesAmout); //intermediate state
	
	std::vector<std::pair<int, double>> currentNonZeroTransitions;//non-zero matrix elements of spin matrixes
	std::vector<State> tempWF, tempWF2; //intermediate wavfunctions

	int second_ort;
	double curE, E0;

	//initialisation
	E0 = pairOperator.getE0(inWF.getNodesAmount());
	
	//computation
	for (unsigned int inSt = 0; inSt < inWF.getEigenstatesAmount(); inSt++)
	{
		currentInputState = inWF.getEigenstateByNumber(inSt);

		for (auto const& curInteraction:interactions[interNumber]) //перебираем все эл-ты взаимодействия
		{
			for (int ort = 0; ort<OrtsAmount; ort++)
			{
				tempWF.clear();//очищаем временный массив состояний, важно для y и z компонент
				currentNonZeroTransitions = vOperator.getNonZeroElements(curInteraction.v1, ort, currentInputState.getStateByNumber(curInteraction.n1));
				for (auto const& nonZeroElem: currentNonZeroTransitions)//iterate over all nonzero matrixElements
				{
					tempst.setFactor(currentInputState.getFactor()*nonZeroElem.second);
					if (ort != 2)//In case of Sp or Sm there is factor 0.5
						tempst.multiplicateFactor(0.5);

					//copy old states and update one
					tempst.copyStates(currentInputState);
					tempst.setStateByNumber(curInteraction.n1, nonZeroElem.first);

					//copy powers and increase one
					tempst.copyPowers(currentInputState);
					tempst.incPower(curInteraction.Jtype);

					//add current term
					tempWF.push_back(tempst);
					
				}
				switch (ort) //S1*S2=0.5*(Sp1*Sm2+Sm1*Sp2)+Sz1*Sz2
				{
				case 0: second_ort = 1; break;
				case 1: second_ort = 0; break;
				case 2: second_ort = 2; break;
				}
				for (int k = 0; k<tempWF.size(); k++) //iterate over intermediate state
				{
					currentNonZeroTransitions = vOperator.getNonZeroElements(curInteraction.v2, second_ort, tempWF[k].getStateByNumber(curInteraction.n2));
					
					for (auto const& nonZeroElem: currentNonZeroTransitions)//iterate over all nonzero matrixElements
					{
						//copy old states and update one
						tempst.copyStates(tempWF[k]);
						tempst.setStateByNumber(curInteraction.n2, nonZeroElem.first);

						//calculate Energy of the current state
						curE = tempst.getEnergie(vOperator.getEnergiesOfStates());

						switch(type)
						{
						case 1:
							if(curE != E0)
							{
								//calculate final factor
								tempst.setFactor(tempWF[k].getFactor()*nonZeroElem.second);
								//copy Povers of J factor
								tempst.copyPowers(tempWF[k]);
								//add cur state to intermediate output vector
								tempWF2.push_back(tempst);  
							}
							break;
						case 2:
							if (curE == E0)
							{
								//calculate final factor
								tempst.setFactor(tempWF[k].getFactor()*nonZeroElem.second);
								//copy Povers of J factor
								tempst.copyPowers(tempWF[k]);
								//add cur state to intermediate output vector
								tempWF2.push_back(tempst);  
							}
							break;
						case 3:
							if (curE != E0)
							{
								tempst.setFactor(tempWF[k].getFactor()*nonZeroElem.second/(E0-curE));
								//copy Povers of J factor
								tempst.copyPowers(tempWF[k]);
								//add cur state to intermediate output vector
								tempWF2.push_back(tempst);  
							}
							break;
						case 4:
							if (curE != E0)
							{
								//calculate final factor
								tempst.setFactor(tempWF[k].getFactor()*nonZeroElem.second/pow(E0-curE,power));
								//copy Povers of J factor
								tempst.copyPowers(tempWF[k]);
								//add cur state to intermediate output vector
								tempWF2.push_back(tempst);  
							}
							break;
						}
					}
				}
			}
		}
	}
	//Сортируем и собираем выходной вектор
	outWF.clear(inWF.getNodesAmount());
	if (tempWF2.size())
		outWF.collect(tempWF2);
}

void WFTransformer::actPairMatrix(WaveFunction& inWF, WaveFunction& outWF, int interNumber, int type, int power)
{
	int nodesAmout = inWF.getNodesAmount();
	outWF.setNodesAmount(nodesAmout);

	State currentInputState;//const state from 
	double curEnergieOfState;
	double groundE = pairOperator.getE0(nodesAmout);
	State tmpState, tmpState2; //tmpState2 - for quatro case
	//int plaquetNumber[MaxPlaquetsPerInteraction];
	
	bool flag = false;

	int operatorType;//Pair -0, Quadro -1;
	int n1, n2, n3, n4;  //for quadro case n1-top left
	int newN1, newN2, newN3, newN4;
	int row,row2;


	std::vector<State> intermediateStorage;

	ExtendedInter curInterElem = extendedInteractions[interNumber];
	{
				
		switch (curInterElem.plaquetsAmount)
		{
		case 2:
			operatorType = 0;
			break;
		case 4: 
			operatorType = 1;
			break;
		}

		for (unsigned int inSt = 0; inSt < inWF.getEigenstatesAmount(); inSt++) //enumerate all elems of input WaveFuction
		{
			if (operatorType == 0)
			{
				//current state to act
				currentInputState = inWF.getEigenstateByNumber(inSt); //peek element from input wave function to work with
				
				n1 = curInterElem.n[0]; //number of the array's cell with the first state to change
				n2 = curInterElem.n[1]; //number of the array's cell with the second state to change
				
				//get the row corresponding to current pair of states
				row = pairOperators::pairStatesToRow(currentInputState.getStateByNumber(n1), currentInputState.getStateByNumber(n2));
				

				//iterate over all matrixes in current term
				/*if (DEBUG)
				{
					std::cout << "\nALARM!!!!!!!!!!!!!!\nALARM!!!!!!!!!!!!!!\nALARM!!!!!!!!!!!!!!\nALARM!!!!!!!!!!!!!!\nALARM!!!!!!!!!!!!!!\nALARM!!!!!!!!!!!!!!\nALARM!!!!!!!!!!!!!!\nALARM!!!!!!!!!!!!!!\n";
					std::cout << "change \"i\" in the next loop!!!\n\n\n";
				}*/
				for (int i = 0; i < 2; i++)
				{
					//iterate over all transitions
					for (auto &curOperatorMatrixElem : pairOperator.opMatrixNonZero[curInterElem.operatorType[i]][row])
					{

						//copy old parameters
						tmpState.copyStates(currentInputState);
						tmpState.copyPowers(currentInputState);
						tmpState.setFactor(currentInputState.getFactor());
						//get new states
						pairOperators::columnToPairStates(curOperatorMatrixElem.first, newN1, newN2);
						//set new states
						tmpState.setStateByNumber(n1, newN1);
						tmpState.setStateByNumber(n2, newN2);

						curEnergieOfState = tmpState.getEnergie(pairOperator.getEnergiesOfStates());


						//increase J-factor/Q-factor
						if (DEBUG_IMPORTANT_NOTES) std::cout << "\n Special case for J2=0 \n";
						if(curInterElem.Jtype[i]!=2)
							tmpState.incPower(curInterElem.Jtype[i]);
						else
						{
							tmpState.incPower(0);
							tmpState.multiplicateFactor(-1);
						}

						//change factor

						flag = false;
						switch (type)
						{
						case 1:
							if (curEnergieOfState != groundE) { tmpState.multiplicateFactor(curOperatorMatrixElem.second); flag = true; }
							break;
						case 2:
							if (curEnergieOfState == groundE) { tmpState.multiplicateFactor(curOperatorMatrixElem.second);  flag = true; }
							break;
						case 3:
							if (curEnergieOfState != groundE) { tmpState.multiplicateFactor(curOperatorMatrixElem.second / (groundE - curEnergieOfState));  flag = true; }
							break;
						case 4:
							if (curEnergieOfState != groundE) { tmpState.multiplicateFactor(curOperatorMatrixElem.second / pow(groundE - curEnergieOfState, power));  flag = true; }
							break;
						}
						if (flag)
						{	
							intermediateStorage.push_back(tmpState);
							//testMode
							//std::cout << "inSt: " << inSt << "add\n";
						}
					}
				}
			}

			//quatro-operator case
			if (operatorType == 1)
			{
				currentInputState = inWF.getEigenstateByNumber(inSt); //peek element from input wave function to work with
				//n1-n2 - horisontal bond
				//n3-n4 - vertical bond always

				
				//term Type=0: horisontal-horisontal
				//term Type=1: vertical-ertical
				for (int termType = 0; termType <= 1; termType++)
				{
					if (termType == 0) //vertical case
					{
						n1 = curInterElem.n[0]; //number of the array's cell with the 1st state to change; top-left
						n2 = curInterElem.n[1]; //number of the array's cell with the 2nd state to change; top-right
						n3 = curInterElem.n[2]; //number of the array's cell with the 3rd state to change; bottom-left
						n4 = curInterElem.n[3]; //number of the array's cell with the 4th state to change; bottom-right
					}
					else//vertical case
					{
						n1 = curInterElem.n[0]; //number of the array's cell with the 1st state to change; top-left
						n2 = curInterElem.n[2]; //number of the array's cell with the 3rd state to change; bottom-left
						n3 = curInterElem.n[1]; //number of the array's cell with the 2nd state to change; top-right
						n4 = curInterElem.n[3]; //number of the array's cell with the 4th state to change; bottom-right
					}
					
					row = pairOperators::pairStatesToRow(currentInputState.getStateByNumber(n1), currentInputState.getStateByNumber(n2));
					for (auto &curOperatorMatrixElem : pairOperator.opMatrixNonZero[curInterElem.operatorType[2 * termType + 0]][row])
					{
						//copy old parameters
						tmpState.setFactor(currentInputState.getFactor());
						tmpState.copyStates(currentInputState);
						tmpState.copyPowers(currentInputState);
						//get new states
						pairOperators::columnToPairStates(curOperatorMatrixElem.first, newN1, newN2);
						//set new states
						tmpState.setStateByNumber(n1, newN1);
						tmpState.setStateByNumber(n2, newN2);

						curEnergieOfState = tmpState.getEnergie(pairOperator.getEnergiesOfStates());

						//change factor
						tmpState.multiplicateFactor(curOperatorMatrixElem.second);

						//start acting by second matrix
						row2 = pairOperators::pairStatesToRow(currentInputState.getStateByNumber(n3), currentInputState.getStateByNumber(n4));
						//iterate over second multiplayer
						for (auto &curOperatorMatrixElem2 : pairOperator.opMatrixNonZero[curInterElem.operatorType[2 * termType + 1]][row2])
						{
							//copy old parameters
							tmpState2.setFactor(tmpState.getFactor());
							tmpState2.copyStates(tmpState);
							tmpState2.copyPowers(tmpState);
							//get new states
							pairOperators::columnToPairStates(curOperatorMatrixElem2.first, newN3, newN4);
							//set new states
							tmpState2.setStateByNumber(n3, newN3);
							tmpState2.setStateByNumber(n4, newN4);

							curEnergieOfState = tmpState2.getEnergie(pairOperator.getEnergiesOfStates());


							//increase J-factor
							tmpState2.incPower(curInterElem.Jtype[2 * termType + 1]);
							flag = false;
							switch (type)
							{
							case 1:
								if (curEnergieOfState != groundE) {
									tmpState2.multiplicateFactor(curOperatorMatrixElem2.second);
									flag = true;
								}
								break;
							case 2:
								if (curEnergieOfState == groundE) {
									tmpState2.multiplicateFactor(curOperatorMatrixElem2.second);
									flag = true;
								}
								break;
							case 3:
								if (curEnergieOfState != groundE) {
									tmpState2.multiplicateFactor(curOperatorMatrixElem2.second / (groundE - curEnergieOfState));
									flag = true;
								}
								break;
							case 4:
								if (curEnergieOfState != groundE) {
									tmpState2.multiplicateFactor(curOperatorMatrixElem2.second / pow(groundE - curEnergieOfState, power));
									flag = true;
								}
								break;
							}
							if (flag)
								//outWF.addEigenState(tmpState2);
								intermediateStorage.push_back(tmpState2);
						}
					}
				}
			}
		}
	}
	//testMode
	std::cout << "  interWF size before collect: " << intermediateStorage.size()  << "\n";
	if (intermediateStorage.size())
		outWF.collect(intermediateStorage);
	//testMode
	std::cout << "  interWF size after collect: " << outWF.getEigenstatesAmount() << "\n";
}

void WFTransformer::actInside(WaveFunction& inWF, WaveFunction& outWF, int plaquetNumber, int type, int power)
{
	State currentInputState;//const state from 
	State tmpState(inWF.getNodesAmount()); //intermediate state

	std::vector<std::pair<int, double>> currentNonZeroTransitions;//non-zero matrix elements of spin matrixes
	std::vector<State> tempWF; //intermediate wavfunctions

	double curE, E0;
	
	//initialisation
	E0 = vOperator.getE0(inWF.getNodesAmount());

	//computation
	for (int inSt = 0; inSt<inWF.getEigenstatesAmount(); inSt++)
	{
		currentInputState = inWF.getEigenstateByNumber(inSt);
		currentNonZeroTransitions = vOperator.getNonZeroElementsInsideOperator(inWF.getEigenstateByNumber(inSt).getStateByNumber(plaquetNumber));

		for (auto nonZeroElem: currentNonZeroTransitions)
		{
			tmpState.copyStates(currentInputState);
			tmpState.setStateByNumber(plaquetNumber, nonZeroElem.first);

			curE = tmpState.getEnergie(vOperator.getEnergiesOfStates());

				switch (type)
				{
				case 5:
					if (E0 != curE)
					{
						tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second);

						tmpState.copyPowers(currentInputState);

						if (DEBUG_IMPORTANT_NOTES) std::cout << "\n Special case for J2=0 \n";
						//start special case
						tmpState.incPower(0);
						tmpState.multiplicateFactor(-1);
						//end special case

						tempWF.push_back(tmpState);
					}
					break;
				case 6:
					if (E0 != curE)
					{
						tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second/pow(E0-curE,power));

						tmpState.copyPowers(currentInputState);
						
						if (DEBUG_IMPORTANT_NOTES) std::cout << "\n Special case for J2=0 \n";
						//start special case
						tmpState.incPower(0);
						tmpState.multiplicateFactor(-1);
						//end special case

						tempWF.push_back(tmpState);
					}
					break;
				case 7:
					if (E0 == curE)
					{
						tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second);

						tmpState.copyPowers(currentInputState);
						
						if (DEBUG_IMPORTANT_NOTES) std::cout << "\n Special case for J2=0 \n";
						//start special case
						tmpState.incPower(0);
						tmpState.multiplicateFactor(-1);
						//end special case

						tempWF.push_back(tmpState);
					}
					break;
				}

			
		}
	}
	///todo
	//TODO
	//check it
	//check it
	//check it
	//check it
	//check it
	outWF.clear(inWF.getNodesAmount());
	if (tempWF.size())
		outWF.collect(tempWF);
}

void WFTransformer::actPairInside(WaveFunction& inWF, WaveFunction& outWF, int plaquetNumber, int type, int power)
{
	State currentInputState;//const state from 
	State tmpState(inWF.getNodesAmount()); //intermediate state

	std::vector<std::pair<int, double>> currentNonZeroTransitions;//non-zero matrix elements of spin matrixes
	std::vector<State> tempWF; //intermediate wavfunctions

	double curE, E0;

	//initialisation
	E0 = pairOperator.getE0(inWF.getNodesAmount());

	//computation
	for (int inSt = 0; inSt<inWF.getEigenstatesAmount(); inSt++)
	{
		currentInputState = inWF.getEigenstateByNumber(inSt);
		

		for (auto nonZeroElem : pairOperator.opMatrixJInsideNonZero[inWF.getEigenstateByNumber(inSt).getStateByNumber(plaquetNumber)])
		{
			tmpState.clear();
			tmpState.copyStates(currentInputState);
			tmpState.setStateByNumber(plaquetNumber, nonZeroElem.first);

			curE = tmpState.getEnergie(pairOperator.getEnergiesOfStates());

			switch (type)
			{
			case 5:
				if (E0 != curE)
				{
					tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second);

					tmpState.copyPowers(currentInputState);

					if (DEBUG_IMPORTANT_NOTES) std::cout << "\n Special case for J2=0 \n";
					//start special case
					tmpState.incPower(0);
					tmpState.multiplicateFactor(-1);
					//end special case

					tempWF.push_back(tmpState);
				}
				break;
			case 6:
				if (E0 != curE)
				{
					tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second / pow(E0 - curE, power));

					tmpState.copyPowers(currentInputState);

					if (DEBUG_IMPORTANT_NOTES) std::cout << "\n Special case for J2=0 \n";
					//start special case
					tmpState.incPower(0);
					tmpState.multiplicateFactor(-1);
					//end special case

					tempWF.push_back(tmpState);
				}
				break;
			case 7:
				if (E0 == curE)
				{
					tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second);

					tmpState.copyPowers(currentInputState);

					if (DEBUG_IMPORTANT_NOTES) std::cout << "\n Special case for J2=0 \n";
					//start special case
					tmpState.incPower(0);
					tmpState.multiplicateFactor(-1);
					//end special case

					tempWF.push_back(tmpState);
				}
				break;
			}
		}


		//Q-inside matrix
		for (auto nonZeroElem : pairOperator.opMatrixQInsideNonZero[inWF.getEigenstateByNumber(inSt).getStateByNumber(plaquetNumber)])
		{
			tmpState.clear();
			tmpState.copyStates(currentInputState);
			tmpState.setStateByNumber(plaquetNumber, nonZeroElem.first);

			curE = tmpState.getEnergie(pairOperator.getEnergiesOfStates());

			switch (type)
			{
			case 5:
				if (E0 != curE)
				{
					tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second);

					tmpState.copyPowers(currentInputState);

					tmpState.incPower(1);//Q-power

					tempWF.push_back(tmpState);
				}
				break;
			case 6:
				if (E0 != curE)
				{
					tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second / pow(E0 - curE, power));

					tmpState.copyPowers(currentInputState);

					tmpState.incPower(1);
					
					tempWF.push_back(tmpState);
				}
				break;
			case 7:
				if (E0 == curE)
				{
					tmpState.setFactor(currentInputState.getFactor()*nonZeroElem.second);

					tmpState.copyPowers(currentInputState);

					tmpState.incPower(1);
					
					tempWF.push_back(tmpState);
				}
				break;
			}
		}
	}
	
	outWF.clear(inWF.getNodesAmount());
	if (tempWF.size())
		outWF.collect(tempWF);
}



