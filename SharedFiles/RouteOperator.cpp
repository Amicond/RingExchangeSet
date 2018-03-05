#include "stdafx.h"
#include "RouteOperator.h"

const int RouteOperator::baseOperatorsAmount = 3;
int RouteOperator::getAmountOfBaseOperators() 
{
	return baseOperatorsAmount;
}



RouteOperator::RouteOperator(int operatorType,Point startPoint)
{
	sorted = false;
	Point shift;
	if (operatorType > baseOperatorsAmount)
		std::cout << "Warning!\n\n\n";
	
	switch (operatorType)
	{
	case 0:
		//extended horisontal right
		type = 0;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 2);
		shift.set(1, 0);
		this->addShift(shift + startPoint, 2);
		break;
	case 1:
		//extended vertical up
		type = 1;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 2);
		shift.set(0, 1);
		this->addShift(shift + startPoint, 2);
		break;

	case 2:
		//extended diagonal up-right
		type = 2;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 1);
		shift.set(0, 1);
		this->addShift(shift + startPoint, 1);
		shift.set(1, 1);
		this->addShift(shift + startPoint, 1);
		shift.set(1, 0);
		this->addShift(shift+ startPoint, 1);
		break;
	
	default:
			type = -1;
	}	
	sortNodes();
}

RouteOperator::~RouteOperator()
{
}

void RouteOperator::addShift(Point shift, int degree)
{
	sorted = false;
	std::vector<NodeAndDegree>::iterator curElem;
	for (curElem = shifts.begin(); curElem != shifts.end(); curElem++)
		if (curElem->point == shift)
			break;
	if (curElem == shifts.end())
	{
		shifts.push_back(NodeAndDegree(shift, degree));
	}
	else
	{
		std::cout << curElem->point.getX() << " " << curElem->point.getY() << "\n";
		std::cout << "Error add shift\n\n\n";
	}
	sortNodes();
}


void RouteOperator::sortNodes()
{
	if (sorted) return;
	sort(shifts.begin(), shifts.end());
	sorted = true;
}

//TODO REPLACE SORT FUNCTION
void RouteOperator::moveToPoint(Point shiftingVector)
{
	sorted = false;
	for (auto &elem : shifts)
	{
		elem.point = elem.point - shiftingVector;
	}
	sortNodes();
}

const std::vector<Point> RouteOperator::getPoints() const
{
	std::vector<Point> res;
	for (auto &elem : shifts)
		res.push_back(elem.point);
	return res;
}

const std::vector<std::pair<Point, int>> RouteOperator::getDegreesOfPoints() const
{
	std::vector<std::pair<Point, int>> res;
	for (auto &elem : shifts)
		res.push_back(std::pair<Point, int>(elem.point, elem.degree));
	return res;
}

void RouteOperator::print(std::ostream &out) const
{
	out << type ;
	for (auto &elem : shifts)
	{
		out << "," << "{{" << elem.point.getX() << "," << elem.point.getY() << "}" << elem.degree << "}";
	}
	out << " ";
}

void RouteOperator::parse(std::string inp)
{
	sorted = false;
	shifts.clear();
	int index;
	int nodeAmounts, x, y, degree;
	std::istringstream inpParser;
	std::string tmp;


	index=inp.find_first_of(',');
	tmp = inp.substr(0, index);
	inpParser.str(tmp);
	inpParser >> type;

	if (type == 2 || type == 3)
		nodeAmounts = 4;
	else
		nodeAmounts = 2;

	for (int i = 0; i < nodeAmounts; i++)
	{
		inp = inp.substr(index + 3);
		index = inp.find_first_of(',');
		tmp = inp.substr(0, index);
		inpParser.clear();
		inpParser.str(tmp);
		inpParser >> x;
		inp = inp.substr(index + 1);
		index = inp.find_first_of('}');
		tmp = inp.substr(0, index);
		inpParser.clear();
		inpParser.str(tmp);
		inpParser >> y;
		inp = inp.substr(index+1);
		index = inp.find_first_of('}');
		tmp = inp.substr(0, index);
		inpParser.clear();
		inpParser.str(tmp);
		inpParser >> degree;
		inp = inp.substr(index);		
		shifts.push_back(NodeAndDegree(Point(x, y), degree));
	}
	sortNodes();
}

int RouteOperator::getType() const
{
	return type;
}

bool RouteOperator::operator==(const RouteOperator &second)const
{
	if (type == second.type&&sorted==second.sorted&&sorted==true)
	{
		if(std::mismatch(shifts.begin(), shifts.end(), second.shifts.begin()).first==shifts.end())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool RouteOperator::operator<(const RouteOperator &second)const
{
	if (type < second.type)
		return true;
	if (type == second.type)
	{
		for (int i = 0; i < shifts.size(); i++)
		{
			if (shifts[i] < second.shifts[i])
				return true;
			if (second.shifts[i] < shifts[i] )
				return false;
		}
	}
	return false;
}

void RouteOperator::verticalAxisReflection() 
{
	sorted = false;
	for (auto &elem : shifts)
		elem.point.transformMirrorY();
	sortNodes();
}

void RouteOperator::rotate180()
{
	//type doesn't change
	sorted = false;
	for (auto &elem : shifts)
		elem.point.transformRotate();
	sortNodes();
}

