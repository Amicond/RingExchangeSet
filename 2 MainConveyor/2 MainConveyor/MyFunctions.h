#pragma once
#include "stdafx.h"
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
	char Jtype; // 0-J1, 1-J2, 2-(J2-J1)
};


struct edge //для хранения координат ребер
{
	int x1,y1,x2,y2;

	bool operator==(const edge &e2) const;
	
	void set(int X1, int Y1, int X2, int Y2);

};

int minus1(int *nodeSet, int n);

void eval_cur_route(int r[][2], int OrderLength, int RouteLength, std::vector<edge> &edges, int nodeNumsOfEdges[N][2], std::vector<point> &nodes, int &RealLength);

//осталась от начального случая - переписать или удалить
bool check_cur_operator_set(bool &Res, int OrderLength, int RealLength, int *termorder, int *op_set, std::vector<edge> edges);//проверяем можкт ли быть не 0 по данной конфигурации

void read_Route(int r[][2], std::istringstream &s);

void generate_procedure_order(int *termorder,int* operatororder,int edge_amount,int num,int *Res,int *power);



class InteractionForPairMatrix
{
	static const int halfAmountOfInteractions;
public:
	static void getStatesByRow(int interNumber,int row, int &state1, int &state2);
	static void getRowByStates(int interNumber, int state1, int state2, int &row);
};