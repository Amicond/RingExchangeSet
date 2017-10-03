#pragma once

#include <map>
#include "Point.h"
#include "NodeAndDegree.h"

class RouteOperator
{

	int type;
	std::vector<NodeAndDegree> shifts;
	static const int baseOperatorsAmount;
	
public:
	RouteOperator(int type, Point startPoint = Point(0, 0));
	~RouteOperator();
	
	//setters
	void addShift(Point shift, int degree);//for initialization

	//getters
	int getType();
	static int getAmountOfBaseOperators();
	const std::vector<std::pair<Point, int>> getDegreesOfPoints() const;//get all points and their degrees
	
	//transformations
	void moveToPoint(Point shift); //move 
	void verticalAxisReflection();
	void rotate180();
	
	//input-output
	void parse(std::string inp);
	void print(std::ostream &out); //print "type,{{x1,y1},degree},{{x2,y2},degree} "

	//operators
	bool operator==(const RouteOperator &second)const;
	bool operator<(const RouteOperator &second)const;
	/*bool compare(const RouteOperator &second)const;*/
};

