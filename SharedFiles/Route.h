#ifndef ROUTE_H
#define ROUTE_H

#include "Edge.h"

class Route
{
	std::vector<Edge> edges;
public:
	bool operator ==(const Route &r2) const;
	void generatePoints(std::vector<Point> &points)const;
	void Route::rotate180();
	void Route::mirrorVerticalAxis();
	bool Route::ifShadow();
	int Route::getDegrees(std::vector<int> &vertexDegree, std::vector<Point> &points);
	void Route::getEdges(std::vector<Edge> &uniqEdges, std::vector<int> &uniqEdgesAmount);
	void Route::writeRouteToFile(std::ofstream &out);
	void Route::sortEdges();
	bool Route::compare(Route &v2);
	void Route::shift(Point p);
	void Route::copy(const Route &init);
	int getSize();
	void addEdge(Edge curEdge);
	void removeLastEdge();
	void clear();
};

#endif // !1