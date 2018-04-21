#ifndef __ROUTE_OPERATOR_H__
#define __ROUTE_OPERATOR_H__



#include <map>
#include "Point.h"
#include "NodeAndDegree.h"

class RouteOperator
{
	bool sorted;
	int type;
	std::vector<NodeAndDegree> shifts;
	static const int baseOperatorsAmount;
	
public:
	RouteOperator(int type, Point startPoint = Point(0, 0));
	~RouteOperator();
	
	//setters
	void addShift(Point shift, int degree);//for initialization

	//getters
	int getType() const;
	static int getAmountOfBaseOperators();
	const std::vector<std::pair<Point, int>> getDegreesOfPoints() const;//get all points and their degrees
	const std::vector<Point> getPoints() const;
	
	//transformations
	void moveToPoint(Point shift); //move 
	void verticalAxisReflection();
	void rotate180();
	
	//input-output
	void parse(std::string inp);
	void print(std::ostream &out) const; //print "type,{{x1,y1},degree},{{x2,y2},degree} "

	//operators
	bool operator==(const RouteOperator &second)const;
	bool operator<(const RouteOperator &second)const;
	void sortNodes();

	/*bool compare(const RouteOperator &second)const;*/
};

#endif // !__ROUTE_OPERATOR_H__