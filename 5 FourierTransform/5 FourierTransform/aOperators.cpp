#include "stdafx.h"
#include "aOperators.h"
#include "LadderOperator.h"
#include "cos.h"

bool bilinearFourierLadderOperators::operator==(const bilinearFourierLadderOperators sec) const
{
	if (operatorTypes_.size() != sec.operatorTypes_.size())
		return false;
	for (int i = 0; i < operatorTypes_.size(); i++)
	{
		if (bosonTypes_[i] != sec.bosonTypes_[i])
			return false;
		if (operatorTypes_[i] != sec.operatorTypes_[i])
			return false;
		if (shifts_[i].first != sec.shifts_[i].first)
			return false;
		if (shifts_[i].second != sec.shifts_[i].second)
			return false;
	}
	return true;
} 

//important to set Cos Class
bool bilinearFourierLadderOperators::convertTerm(Term &curTerm)
{
	clear();
	if (curTerm.getTermLength() != 2)
		return false;
	else
	{
		LadderOperator curLadderOperator;
		for (int i = 0; i < curTerm.getOperatorAmount(); i++)
		{
			curLadderOperator=curTerm.getLadderOperator(i);
			std::string curName = curLadderOperator.getName();
			if (curName.find_first_of("N") != std::string::npos)//case of xN_ operator=(xp_)(xm_)
			{
				bosonTypes_.push_back(curName[0]);
				bosonTypes_.push_back(curName[0]);
				operatorTypes_.push_back('p');
				operatorTypes_.push_back('m');
				int da, db;
				Cos::findCos(curLadderOperator.getNodeNumber(), da, db);
				shifts_.push_back(std::pair<int,int>(da, db));
				shifts_.push_back(std::pair<int, int>(da, db));
			}
			else
			{
				bosonTypes_.push_back(curName[0]);
				operatorTypes_.push_back(curName[1]);
				int da, db;
				Cos::findCos(curLadderOperator.getNodeNumber(), da, db);
				shifts_.push_back(std::pair<int, int>(da, db));
			}
		}
	}
}

bool bilinearFourierLadderOperators::operator<(const bilinearFourierLadderOperators sec) const
{
	if (operatorTypes_.size() < sec.operatorTypes_.size()) return true;
	else if (operatorTypes_.size() > sec.operatorTypes_.size()) return false;
	for (int i = 0; i < operatorTypes_.size(); i++)	{
		if (operatorTypes_[i] < sec.operatorTypes_[i]) return true;
		else if (operatorTypes_[i] > sec.operatorTypes_[i]) return false;
	
		if (bosonTypes_[i] < sec.bosonTypes_[i])return true;
		else if (bosonTypes_[i]>sec.bosonTypes_[i])return false;

		if (shifts_[i].first < sec.shifts_[i].first) return true;
		else if (shifts_[i].first > sec.shifts_[i].first) return false;

		if (shifts_[i].second < sec.shifts_[i].second) return true;
		else if (shifts_[i].second > sec.shifts_[i].second) return false;
		
	}
	return false;
}



void bilinearFourierLadderOperators::printAterm(std::ofstream &F, bool if_print_coeff)const
{
	if (operatorTypes_.size() == 2)
	{
		std::string subs[2];
		if (if_print_coeff)
			F << coefficient_ << "*";
		if (operatorTypes_[0] == 'm'&& operatorTypes_[1] == 'm')
		{
			subs[0] = "k";
			subs[1] = "-k";
		}
		if (operatorTypes_[0] == 'm'&& operatorTypes_[1] == 'p')
		{
			subs[0] = "k";
			subs[1] = "k";
		}
		if (operatorTypes_[0] == 'p'&& operatorTypes_[1] == 'm')
		{
			subs[0] = "k";
			subs[1] = "k";
		}
		if (operatorTypes_[0] == 'p'&& operatorTypes_[1] == 'p')
		{
			subs[0] = "k";
			subs[1] = "-k";
		}
		for (int i = 0; i < 2; i++)
		{
			F << "Subscript[" << bosonTypes_[i];
			if (operatorTypes_[i] == 'p') F << "p";
			F << "," << subs[i] << "]";
		}


		if (shifts_[0] != shifts_[1])
		{
			F << "*Cos[";
			switch ((shifts_[1].first - shifts_[0].first)){
				case  0: break;
				case -1: F << "-ka"; break;
				case  1: F << "ka"; break;
				default: F << "ka*" << (shifts_[1].first - shifts_[0].first);
			}
			switch ((shifts_[1].second - shifts_[0].second)){
			case 0: break;
			case -1: F << "-kb"; break;
			case 1: F << "+kb"; break;
			default: F << "+kb*" << (shifts_[1].second - shifts_[0].second);
			}
			F << "]";
		}
	}
	else
	{
		F << "\n\n Strange length \n\n";
	}
}

void bilinearFourierLadderOperators::clear()
{
	operatorTypes_.clear();
	shifts_.clear();
	bosonTypes_.clear();
	double coeff = 0;
	int order = 0;
}

//Hash functions for unordered maps
namespace std {
	template <>
	struct hash<bilinearFourierLadderOperators>
	{
		std::size_t operator()(const bilinearFourierLadderOperators& k) const
		{
			std::ostringstream out;
			out << " " << k.coefficient_ << " " << k.operatorTypes_.size();
			for (auto elem : k.operatorTypes_)
				out << elem << " ";
			for (auto elem : k.bosonTypes_)
				out << elem << " ";
			for (auto elem : k.shifts_)
				out << elem.first << " "<<elem.second << " ";
			return (std::hash<string>()(out.str()));
		}
	};
}