#ifndef __MY_fUNCTIONS_H__
#define __MY_fUNCTIONS_H__


#include "stdafx.h"
#include "globalConsts.h"
#include "Consts.h"
#include "Results.h"
#include "JFactors.h"
#include "State.h"

struct point
{
	int sx;
	int sy;

	point(int x, int y);
		
	bool operator==(const point& s2) const;
};

struct inter
{
	char n1,n2; //номера плакетов, нумерация с 0
	char v1,v2; //номера вершин, нумерация с 0
	char Jtype; //names and order defined in JFactors.cpp
};

struct ExtendedInter
{
	int operatorType[MaxMatrixPerInteraction]; //should be consitent with extendedOperator consts
	char Jtype[MaxMatrixPerInteraction]; // 0-J, 1-Q, 2-(-J)
	//in pair case  - two different matrixes 1 for "Q" and 1 for "J"
	//in quatro case - two consequent matrixes

	char plaquetsAmount; //amount of plaquets in current interaction: 2 or 4
	char n[MaxPlaquetsPerInteraction]; //cells' numbers in state array
	
	void clear();
};


struct edge //для хранения координат ребер
{
	int x1,y1,x2,y2;

	bool operator==(const edge &e2) const;
	
	void set(int X1, int Y1, int X2, int Y2);

};

int minus1(int *nodeSet, int n);

void eval_cur_route(int r[][2], int OrderLength, int RouteLength, std::vector<edge> &edges, int nodeNumsOfEdges[N][2], std::vector<point> &nodes, int &RealLength);

void generate_procedure_order(int *termorder,int* operatororder,int edge_amount,int num,int *Res,int *power);

#endif // !__MY_fUNCTIONS_H__

