#include "stdafx.h"
#include "RouteOperator.h"

const int RouteOperator::baseOperatorsAmount = 12;
int RouteOperator::getAmountOfBaseOperators()
{
	return baseOperatorsAmount;
}

RouteOperator::RouteOperator(int operatorType,Point startPoint)
{
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
		//extended horisontal left
		type = 0;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 2);
		shift.set(-1, 0);
		this->addShift(shift + startPoint, 2);
		break;
	case 3:
		//extended vertical down
		type = 1;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 2);
		shift.set(0, -1);
		this->addShift(shift + startPoint, 2);
		break;

	case 4:
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
	case 5:
		//extended diagonal up-left
		type = 3;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 1);
		shift.set(0, 1);
		this->addShift(shift + startPoint, 1);
		shift.set(-1, 1);
		this->addShift(shift + startPoint, 1);
		shift.set(-1, 0);
		this->addShift(shift + startPoint, 1);
		break;
	case 6:
		//extended diagonal down-left
		type = 2;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 1);
		shift.set(0, -1);
		this->addShift(shift + startPoint, 1);
		shift.set(-1, -1);
		this->addShift(shift + startPoint, 1);
		shift.set(-1, 0);
		this->addShift(shift + startPoint, 1);
		break;
	case 7:
		//extended diagonal down-right
		type = 3;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 1);
		shift.set(0, -1);
		this->addShift(shift + startPoint, 1);
		shift.set(1, -1);
		this->addShift(shift + startPoint, 1);
		shift.set(1, 0);
		this->addShift(shift + startPoint, 1);
		break;
	
	

	case 8:
		//simple diagonal up-right
		type = 4;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 1);
		shift.set(1, 1);
		this->addShift(shift + startPoint, 1);
		break;
	case 9:
		//simple diagonal up-left
		type = 5;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 1);
		shift.set(-1, 1);
		this->addShift(shift + startPoint, 1);
		break;
	case 10:
		//simple diagonal down-left
		type = 4;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 1);
		shift.set(-1, -1);
		this->addShift(shift + startPoint, 1);
		break;
	case 11:
		//simple diagonal down-right
		type = 5;
		shift.set(0, 0);
		this->addShift(shift + startPoint, 1);
		shift.set(1, -1);
		this->addShift(shift + startPoint, 1);
		break;
	
	
	default:
			type = -1;
	}	
	sort(this->shifts.begin(), this->shifts.end());
}

RouteOperator::~RouteOperator()
{
}

void RouteOperator::addShift(Point shift, int degree)
{
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

}

void RouteOperator::moveToPoint(Point shiftingVector)
{
	for (auto &elem : shifts)
	{
		elem.point = elem.point - shiftingVector;
	}
	sort(this->shifts.begin(), this->shifts.end());
}

const std::vector<std::pair<Point, int>> RouteOperator::getDegreesOfPoints() const
{
	std::vector<std::pair<Point, int>> res;
	for (auto &elem : shifts)
		res.push_back(std::pair<Point, int>(elem.point, elem.degree));
	return res;
}

void RouteOperator::print(std::ostream &out)
{
	out << type ;
	for (auto &elem : shifts)
	{
		out << "," << "{{" << elem.point.getX() << "," << elem.point.getY() << "}" << elem.degree << "}";
	}
	out << " ";
}

int RouteOperator::getType()
{
	return type;
}

bool RouteOperator::operator==(const RouteOperator &second)const
{
	if (type == second.type)
	{
		int size = shifts.size();
		for (int i = 0; i < size; i++)
			if (!(shifts[i] == second.shifts[i]))
				return false;
		return true;
	}
	else
		return false;
}

//bool RouteOperator::compare(const RouteOperator &second)const
//{
//	if (type == second.type)
//	{
//		int size = shifts.size();
//		for (int i = 0; i < size; i++)
//			if (!(shifts[i] == second.shifts[i]))
//				return false;
//		return true;
//	}
//	else
//		return false;
//}

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
	switch (type)
	{
	case 2:
		type = 3; break;
	
	case 3:
		type = 2; break;
	
	
	case 4:
		type = 5; break;
	case 5:
		type = 4; break;

	}
	for (auto &elem : shifts)
		elem.point.transformMirrorY();
	sort(shifts.begin(), shifts.end());
}

void RouteOperator::rotate180()
{
	//type doesn't change

	for (auto &elem : shifts)
		elem.point.transformRotate();
	sort(shifts.begin(), shifts.end());
}

