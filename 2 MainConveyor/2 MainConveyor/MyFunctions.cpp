#include "stdafx.h"
#include "MyFunctions.h"


////////////////////  point   //////////////////////////////////////////////////////

void ExtendedInter::clear()
{
	//this->
	for (int i = 0; i < MaxMatrixPerInteraction; i++)
	{
		Jtype[i] = -1;
		operatorType[i] = -1;
	}
	for (int i = 0; i < MaxPlaquetsPerInteraction; i++)
		n[i] = -1;
	plaquetsAmount = -1;
}


point::point(int x, int y)
{
	sx = x;
	sy = y;
}

bool point::operator==(const point& s2) const
{
	if ((sx == s2.sx) && (sy == s2.sy))
	{
		return true;
	}
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////



////////////////////  edge   //////////////////////////////////////////////////////

bool edge::operator==(const edge &e2) const
{
	if (((x1 == e2.x1) && (x2 == e2.x2) && (y1 == e2.y1) && (y2 == e2.y2)) || ((x1 == e2.x2) && (x2 == e2.x1) && (y1 == e2.y2) && (y2 == e2.y1)))
	{
		return true;
	}
	else
		return false;
}

void edge::set(int X1, int Y1, int X2, int Y2)
{
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
}

//////////////////////////////////////////////////////////////////////////


///////////////////////////////   functions ///////////////////////////////////////////
int minus1(int *nodeSet, int n) //вычисляем знак для текущего слагаемого в рду теории возмущения
{
	if (n == 1) return 1;//для первого порядка


	int res = 1;
	//считаем кол-во нулей
	for (int i = 0; i<n - 1; i++)
	{
		if (nodeSet[i] == 0)
			res *= -1;
	}
	return res;
}

void eval_cur_route(int r[][2], int OrderLength, int RouteLength, std::vector<edge> &edges, int nodeNumsOfEdges[N][2], std::vector<point> &nodes, int &RealLength)
//заполняет для данного маршрута список ребер и их количество
{
	for (int i = 0; i<N; i++)
	{
		nodeNumsOfEdges[i][0] = 0;
		nodeNumsOfEdges[i][1] = 0;
	}
	//Проверяем реальную длину маршрута+ строим маску - сколько раз каждое ребро должно встречаться
	int numberOfEdges[10];//число ребер
	edge cur;
	bool flag;
	RealLength = 0;//Реальное количество различных "ГЛАВНЫХ" операторов
	edges.clear();
	for (int i = 0; i<10; i++)
	{
		numberOfEdges[i] = 0;
	}
	for (int i = 0; i<2 * RouteLength; i += 2)//список ребер
	{
		cur.set(r[i][0], r[i][1], r[i + 1][0], r[i + 1][1]);
		flag = true;
		for (unsigned int j = 0; j<edges.size(); j++)
		{
			if (cur == edges[j])
			{
				flag = false;
				numberOfEdges[j]++;
			}
		}
		if (flag)
		{
			edges.push_back(cur);
			numberOfEdges[edges.size() - 1]++;
		}
	}
	nodes.clear();
	//nodes.push_back(point(r[0][0],r[0][1]));
	for (int i = 0; i<2 * RouteLength; i++)//вычисляем номера вершин
	{
		if (find(nodes.begin(), nodes.end(), point(r[i][0], r[i][1])) == nodes.end())
			nodes.push_back(point(r[i][0], r[i][1]));
	}
	for (unsigned int i = 0; i<edges.size(); i++)//заполняем номера в "nodes" начала и конца для каждого ребра из "edges"
	{
		nodeNumsOfEdges[i][0] = distance(nodes.begin(), find(nodes.begin(), nodes.end(), point(edges[i].x1, edges[i].y1)));
		nodeNumsOfEdges[i][1] = distance(nodes.begin(), find(nodes.begin(), nodes.end(), point(edges[i].x2, edges[i].y2)));
	}
	RealLength = edges.size();
}


void generate_procedure_order(int *termorder, int* operatororder, int edge_amount, int num, int *Res, int *power)
{
	//первый порядок отдельно
	if (num == 1)
	{
		power[0] = 0;
		if (edge_amount == 1)
			Res[0] = 2;
		else
			Res[0] = 7;
		return;
	}
	//общий случай для остальных порядков
	for (int i = 0; i<num; i++)
	{
		power[i] = 0;
	}
	for (int i = 0; i<(num + 1) / 2; i++)
	{
		if (termorder[i] == 0)//ground группа
		{
			if (operatororder[i]<edge_amount)//реберный оператор
				Res[i] = 2;
			else
				Res[i] = 7;
		}
		else if (termorder[i] == 1)//знаменатель в 1ой степени
		{
			if (operatororder[i] < edge_amount)
			{
				Res[i] = 3;
				power[i] = 1;
			}
			else
			{
				Res[i] = 6;
				power[i] = 1;
			}

		}
		else
		{
			if (operatororder[i]<edge_amount)
				Res[i] = 4;
			else
				Res[i] = 6;
			power[i] = termorder[i];
		}
	}

	//обратный ход
	for (int i = 0; i<(num / 2); i++)
	{
		if (termorder[num - i - 2] == 0)//ground группа
		{
			if (operatororder[num - i - 1]<edge_amount)//реберный оператор
				Res[num - i - 1] = 2;
			else
				Res[num - i - 1] = 7;
		}
		else if (termorder[num - i - 2] == 1)//знаменатель в 1ой степени
		{
			if (operatororder[num - i - 1] < edge_amount)
			{
				Res[num - i - 1] = 3;
				power[num - i - 1] = 1;
			}
			else
			{
				Res[num - i - 1] = 6;
				power[num - i - 1] = 1;
			}

		}
		else
		{
			if (operatororder[num - i - 1]<edge_amount)
				Res[num - i - 1] = 4;
			else
				Res[num - i - 1] = 6;
			power[num - i - 1] = termorder[num - i - 2];
		}
	}
	//самый последний элемент обратного хода без знаменателя
	if ((Res[num - num / 2] == 3) || (Res[num - num / 2] == 4))
		Res[num - num / 2] = 1;
	if (Res[num - num / 2] == 6)
		Res[num - num / 2] = 5;

}



