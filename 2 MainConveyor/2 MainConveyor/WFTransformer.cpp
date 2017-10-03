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

void WFTransformer::returnPairVOperator(int operatorNum,int nodeNumsOfEdge,std::vector<RouteOperator> operators)
{
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
	E0 = vOperator.getE0(inWF.getNodesAmount());
	
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
	State tmpState;
	//int plaquetNumber[MaxPlaquetsPerInteraction];
	
	for (auto &interElem : extInteractions[interNumber])//enumerate all terms of current interaction
	{
		int operatorType;//Pair -0, Quadro -1;
		int n1, n2, n3, n4;
		int newN1, newN2;
		int row;
		
		switch (interElem.plaquetsAmount)
		{
		case 2:
			operatorType = 0;
			break;
		case 4: 
			operatorType = 0;
			break;
		}

		for (unsigned int inSt = 0; inSt < inWF.getEigenstatesAmount(); inSt++)
		{
			if (operatorType == 0)
			{
				//current state to act
				currentInputState = inWF.getEigenstateByNumber(inSt);
				
				n1 = interElem.n[0]; //number of the array's cell with the first state to change
				n2 = interElem.n[1]; //number of the array's cell with the second state to change
				
				//get the row corresponding to current pair of states
				row = pairOperators::pairStatesToRow(currentInputState.getStateByNumber(n1), currentInputState.getStateByNumber(n2));
				
				//iterate over all transitions
				for (auto &curElem:pairOperator.opMatrixNonZero[interElem.operatorType][row])
				{
					
					//copy old parameters
					tmpState.copyStates(currentInputState);
					tmpState.copyPowers(currentInputState);
					//get new states
					pairOperators::columnToPairStates(curElem.first, newN1, newN2);
					//set new states
					tmpState.setStateByNumber(n1, newN1);
					tmpState.setStateByNumber(n2, newN2);

					curEnergieOfState = tmpState.getEnergie(pairOperator.getEnergiesOfStates());
					
					
					//increase J-factor
					tmpState.incPower(interElem.Jtype);
					
					//change factor
					tmpState.multiplicateFactor(curElem.second);

					switch (type)
					{
					default:
						break;
					}
					
					outWF.addEigenState(tmpState);
				}
			}

			//quatro-operator case
			if (operatorType == 1)
			{

			}
		}
	}
	////Сортируем и собираем выходной вектор
	//outWF.clear(inWF.getNodesAmount());
	//if (tempWF2.size())
	//	outWF.collect(tempWF2);

}

void WFTransformer::actInside(WaveFunction& inWF, WaveFunction& outWF, int plaquetNumber, int type, int power)
{
	State currentInputState;//const state from 
	State tempst(inWF.getNodesAmount()); //intermediate state

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
				tempst.copyStates(currentInputState);
				tempst.setStateByNumber(plaquetNumber, nonZeroElem.first);

				curE = tempst.getEnergie(vOperator.getEnergiesOfStates());

				switch (type)
				{
				case 5:
					if (E0 != curE)
					{
						tempst.setFactor(currentInputState.getFactor()*nonZeroElem.second);

						tempst.copyPowers(currentInputState);
						tempst.incPower(indexOfInsideJOperator);

						tempWF.push_back(tempst);
					}
					break;
				case 6:
					if (E0 != curE)
					{
						tempst.setFactor(currentInputState.getFactor()*nonZeroElem.second/pow(E0-curE,power));

						tempst.copyPowers(currentInputState);
						tempst.incPower(indexOfInsideJOperator);

						tempWF.push_back(tempst);
					}
					break;
				case 7:
					if (E0 == curE)
					{
						tempst.setFactor(currentInputState.getFactor()*nonZeroElem.second);

						tempst.copyPowers(currentInputState);
						tempst.incPower(indexOfInsideJOperator);

						tempWF.push_back(tempst);
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
