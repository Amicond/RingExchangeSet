#include "stdafx.h"
#include "MyFunctions.h"


////////////////////  point   //////////////////////////////////////////////////////

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
int minus1(int *nodeSet, int n) //��������� ���� ��� �������� ���������� � ��� ������ ����������
{
	if (n == 1) return 1;//��� ������� �������


	int res = 1;
	//������� ���-�� �����
	for (int i = 0; i<n - 1; i++)
	{
		if (nodeSet[i] == 0)
			res *= -1;
	}
	return res;
}

void eval_cur_route(int r[][2], int OrderLength, int RouteLength, std::vector<edge> &edges, int nodeNumsOfEdges[N][2], std::vector<point> &nodes, int &RealLength)
//��������� ��� ������� �������� ������ ����� � �� ����������
{
	for (int i = 0; i<N; i++)
	{
		nodeNumsOfEdges[i][0] = 0;
		nodeNumsOfEdges[i][1] = 0;
	}
	//��������� �������� ����� ��������+ ������ ����� - ������� ��� ������ ����� ������ �����������
	int numberOfEdges[10];//����� �����
	edge cur;
	bool flag;
	RealLength = 0;//�������� ���������� ��������� "�������" ����������
	edges.clear();
	for (int i = 0; i<10; i++)
	{
		numberOfEdges[i] = 0;
	}
	for (int i = 0; i<2 * RouteLength; i += 2)//������ �����
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
	for (int i = 0; i<2 * RouteLength; i++)//��������� ������ ������
	{
		if (find(nodes.begin(), nodes.end(), point(r[i][0], r[i][1])) == nodes.end())
			nodes.push_back(point(r[i][0], r[i][1]));
	}
	for (unsigned int i = 0; i<edges.size(); i++)//��������� ������ � "nodes" ������ � ����� ��� ������� ����� �� "edges"
	{
		nodeNumsOfEdges[i][0] = distance(nodes.begin(), find(nodes.begin(), nodes.end(), point(edges[i].x1, edges[i].y1)));
		nodeNumsOfEdges[i][1] = distance(nodes.begin(), find(nodes.begin(), nodes.end(), point(edges[i].x2, edges[i].y2)));
	}
	RealLength = edges.size();
}

bool check_cur_operator_set(bool &Res, int OrderLength, int RealLength, int *termorder, int *operatorSet, std::vector<edge> edges)//��������� ����� �� ���� �� 0 �� ������ ������������
{
	int start = 0;
	int end;
	int mask[10];
	Res = true;
	bool last = false;
	bool ifFind;
	std::vector<point> nodes;
	point currentNode(0, 0);
	for (int i = 0; i<OrderLength; i++)
	{
		if (i == OrderLength - 1)
		{
			end = i;
			last = true;
		}
		if ((termorder[i] == 0) || (last == true))
		{
			end = i;//����� ������
			for (int j = 0; j<10; j++)
				mask[j] = 0;
			for (int j = start; j <= end; j++)
			{
				if ((unsigned int)operatorSet[j]<edges.size())//����� �����
				{
					currentNode.sx = edges[operatorSet[j]].x1; //�������� ��� ������ �������
					currentNode.sy = edges[operatorSet[j]].y1;
					ifFind = false;
					for (unsigned int k = 0; k<nodes.size(); k++)//���� ��
					{
						if (nodes[k] == currentNode)//���� ����� ����������� �� ���-��
						{
							mask[k]++;
							ifFind = true;
						}
					}
					if (!ifFind)//���� �� ����� ���������
					{
						nodes.push_back(currentNode);
						mask[nodes.size() - 1] = 1;
					}

					currentNode.sx = edges[operatorSet[j]].x2;//�������� ��� 2�� �������
					currentNode.sy = edges[operatorSet[j]].y2;
					ifFind = false;
					for (unsigned int k = 0; k<nodes.size(); k++)//���� ��
					{
						if (nodes[k] == currentNode)//���� ����� ����������� �� ���-��
						{
							mask[k]++;
							ifFind = true;
						}
					}
					if (!ifFind)//���� �� ����� ���������
					{
						nodes.push_back(currentNode);
						mask[nodes.size() - 1] = 1;
					}
				}
			}

			for (int j = 0; j<OrderLength; j++)
			{
				if (mask[j] == 1)
				{
					Res = false;
					break;
				}
			}

			if (!Res)
				break;
			start = i + 1;
		}
		if (!Res)
			break;
	}
	return Res;
}

void read_Route(int r[][2], std::istringstream &s)
{
	char c = ' ';
	while (c != 'n')
	{
		s >> c;
	}
	s >> c;//���������� 1 ������
	int num = 0;
	while (N * 2 - 1 >= num)
	{

		s >> r[num][0];
		s >> c;
		s >> r[num][1];
		num++;

		s >> c;
		s >> c;
		s >> c;//���������� 3 �������
		s >> r[num][0];
		s >> c;
		s >> r[num][1];
		num++;
		s >> c;
		s >> c;
	}

}

void generate_procedure_order(int *termorder, int* operatororder, int edge_amount, int num, int *Res, int *power)
{
	//������ ������� ��������
	if (num == 1)
	{
		power[0] = 0;
		if (edge_amount == 1)
			Res[0] = 2;
		else
			Res[0] = 7;
		return;
	}
	//����� ������ ��� ��������� ��������
	for (int i = 0; i<num; i++)
	{
		power[i] = 0;
	}
	for (int i = 0; i<(num + 1) / 2; i++)
	{
		if (termorder[i] == 0)//ground ������
		{
			if (operatororder[i]<edge_amount)//�������� ��������
				Res[i] = 2;
			else
				Res[i] = 7;
		}
		else if (termorder[i] == 1)//����������� � 1�� �������
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

	//�������� ���
	for (int i = 0; i<(num / 2); i++)
	{
		if (termorder[num - i - 2] == 0)//ground ������
		{
			if (operatororder[num - i - 1]<edge_amount)//�������� ��������
				Res[num - i - 1] = 2;
			else
				Res[num - i - 1] = 7;
		}
		else if (termorder[num - i - 2] == 1)//����������� � 1�� �������
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
	//����� ��������� ������� ��������� ���� ��� �����������
	if ((Res[num - num / 2] == 3) || (Res[num - num / 2] == 4))
		Res[num - num / 2] = 1;
	if (Res[num - num / 2] == 6)
		Res[num - num / 2] = 5;

}



////////////////////////////////////////  InteractionForPairMatrix ///////////////////////////////////////////////////////
const int InteractionForPairMatrix::halfAmountOfInteractions = 4;


void InteractionForPairMatrix::getStatesByRow(int interNumber, int row, int &state1, int &state2)
{
	state2 = row%DiffStates;
	state1 = row / DiffStates;
	if (interNumber > halfAmountOfInteractions)
	{
		std::swap(state1, state2);
	}
}

void InteractionForPairMatrix::getRowByStates(int interNumber, int state1, int state2, int &row)
{
	if (interNumber > halfAmountOfInteractions)
	{
		std::swap(state1, state2);
	}
	row = state1*DiffStates + state2;
}
//////////////////////////////////////////////////////////////////////////