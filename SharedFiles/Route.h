#ifndef ROUTE_H
#define ROUTE_H

#include "Edge.h"

class Route
{
	std::vector<Edge> edges;
public:
	bool operator ==(const Route &r2) const;
	void generatePoints(std::vector<Point> &points)const;
	void rotate180();
	void mirrorVerticalAxis();
	bool ifShadow();
	int getDegrees(std::vector<int> &vertexDegree, std::vector<Point> &points);
	void getEdges(std::vector<Edge> &uniqEdges, std::vector<int> &uniqEdgesAmount);
	void writeRouteToFile(std::ofstream &out);
	void sortEdges();
	bool compare(Route &v2);
	void shift(Point p);
	void copy(const Route &init);
	int getSize();
	void addEdge(Edge curEdge);
	void removeLastEdge();
	void clear();
};

#endif // ROUTE_H