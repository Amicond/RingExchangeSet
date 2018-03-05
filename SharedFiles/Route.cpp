#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Route.h"


bool Route::operator==(const Route &r2)const
{
	if (edges.size() != r2.edges.size())
		return false;
	for (int i = 0; i<edges.size(); i++)
		if (!(edges[i] == r2.edges[i]))
			return false;
	return true;
}

void Route::generatePoints(std::vector<Point> &points) const
{
	Point p;
	for (auto &edge:edges)
	{
		p.set(edge.getX1(), edge.getY1());
		if (find(points.begin(), points.end(), p) == points.end())
			points.push_back(p);
		p.set(edge.getX2(), edge.getY2());
		if (find(points.begin(), points.end(), p) == points.end())
			points.push_back(p);
	}
}

void Route::rotate180()
{
	for (auto &edge : edges)
	{
		edge.centralSymmetry();
	}
}

void Route::mirrorVerticalAxis()
{
	for (auto &edge : edges)
	{
		edge.mirrorVerticalAxis();
	}
}

bool Route::ifShadow()//true- «начит уже встречалось в предыдущих пор€дках
{
	std::vector<int> duplicateIndex;
	std::vector<int> amount;
	std::vector<Point> points;
	int degree = getDegrees(amount, points);
	
	for (auto &edge : edges)
	{
		edge.norm();
		duplicateIndex.push_back(-1);
	}
	for (int i = 0; i<edges.size(); i++)
	{
		if (duplicateIndex[i] != -1) continue; //skip edge, that has already checked
		for (int j = i + 1; j<edges.size(); j++)
		{
			if (edges[i] == edges[j])
			{
				duplicateIndex[i] = i;
				duplicateIndex[j] = i;
			}
		}
	}

	//Ќачинаем откидывать ребра с duplicate_index[i]==-1
	Point newPoint;
	int i, j;
	std::vector<Point>::iterator it;
	for (i = 0; i<edges.size(); i++)
	{
		amount.clear();
		points.clear();
		//first edge of such type
		if (duplicateIndex[i] == i)
		{
			for (j = 0; j<edges.size(); j++)
			{
				//skip edge #i
				if (i == j)
					continue;
				//count all other edges
				//starting point
				newPoint.set(edges[j].getX1(), edges[j].getY1());
				it = find(points.begin(), points.end(), newPoint);
				if (it != points.end())
				{
					int k = distance(points.begin(), it);
					amount[k]++;
				}
				else
				{
					points.push_back(newPoint);
					amount.push_back(1);
				}

				//ending point
				newPoint.set(edges[j].getX2(), edges[j].getY2());
				it = find(points.begin(), points.end(), newPoint);
				if (it != points.end())
				{
					int k = distance(points.begin(), it);
					amount[k]++;
				}
				else
				{
					points.push_back(newPoint);
					amount.push_back(1);
				}
			}
			if (count(amount.begin(), amount.end(), 1) == degree)//при отбрасывании повтор€ющегос€ ребра не помен€ла тип, значит повтор
			{
				return true;
			}
		}
	}
	return false;
}


int Route::getDegrees(std::vector<int> &vertexDegree, std::vector<Point> &points)
{
	Point curPoint;
	for (auto &edge:edges)
	{
		curPoint.set(edge.getX1(), edge.getY1());

		std::vector<Point>::iterator it = find(points.begin(), points.end(), curPoint);
		if (it == points.end())
		{
			points.push_back(curPoint);
			vertexDegree.push_back(1);
		}
		else
		{
			vertexDegree[distance(points.begin(), it)]++;
		}


		curPoint.set(edge.getX2(), edge.getY2());
		it = find(points.begin(), points.end(), curPoint); //ищем текущую точку среди уже найденных
		if (it == points.end())
		{
			points.push_back(curPoint); //добавл€ем новую точку
			vertexDegree.push_back(1);
		}
		else
			vertexDegree[distance(points.begin(), it)]++; //увеличиваем степень существующей вершины
	}
	return count(vertexDegree.begin(), vertexDegree.end(), 1);//считаем кол-во вершин со степенью 1
}

void Route::getEdges(std::vector<Edge> &uniqEdges, std::vector<int> &uniqEdgesAmount)
{
	for (auto &routeEdge : edges)
	{
		auto it = find(uniqEdges.begin(), uniqEdges.end(), routeEdge);
		int index;
		if (it == uniqEdges.end())
		{
			uniqEdges.push_back(routeEdge);
			uniqEdgesAmount.push_back(1);
		}
		else
		{
			index = distance(uniqEdges.begin(), it);
			uniqEdgesAmount[index]++;
		}
	}
}

void Route::writeRouteToFile(std::ofstream &out)
{
	//записываем результат в файл
	out << "n ";
	for (auto &edge:edges)
	{
		out << "{" << edge.getX1() << "," << edge.getY1() << "},{" << edge.getX2() << "," << edge.getY2() << "} ";
	}
	out << "\n";
}

void Route::sortEdges()
{
	for (auto &edge : edges)
	{
		edge.norm();
	}
	std::sort(edges.begin(), edges.end());
}

void Route::shift(Point p)
{
	for (auto &edge : edges)
	{
		edge = edge - p;
		edge.norm();
	}
}
bool Route::compare(Route &r2)//на вход v1 подаетс€ отсортированный массив //
{
	this->sortEdges();
	if (edges.size() != r2.edges.size())
		return false;
	Route r2Copy=r2;
	std::vector<Point> routesPoints;
	
	for (int j = 0; j<4; j++)//4 возможных положени€ маршрута
	{
		routesPoints.clear();
		r2Copy.generatePoints(routesPoints);
		for (auto &point: routesPoints)//перебираем точки сдвига
		{
			r2Copy.shift(point);
			r2Copy.sortEdges();
			if (*this == r2Copy)// equal to current route
				return true;
			r2Copy.shift(-point);
		}
		if (j == 1)
			r2Copy.mirrorVerticalAxis();
		else
			r2Copy.rotate180();
	}
	return false;
}

void Route::copy(const Route &init)
{
	edges.clear();
	for (auto &curEdge : init.edges)
	{
		edges.push_back(curEdge);
	}
}

int Route::getSize()
{
	return edges.size();
}


void Route::removeLastEdge()
{
	if (edges.size() > 0)
		edges.pop_back();
}

void Route::clear()
{
	edges.clear();
}

void Route::addEdge(Edge curEdge)
{
	edges.push_back(curEdge);
}