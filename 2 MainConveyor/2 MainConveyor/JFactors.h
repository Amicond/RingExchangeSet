#ifndef __J_FACTORS_H__
#define __J_FACTORS_H__
#include "stdafx.h"


class JFactors
{
public:
	static const unsigned int Npowers = 3;
	static const std::string coefficientNames[Npowers];
private:
	struct JFactor
	{

		//static const int Npowers = 3;
		int powers[JFactors::Npowers];
		bool operator==(const JFactor& jf2)const;
		JFactor(int n[JFactors::Npowers]);
	};
	static const int MaxOrder = 10;
	static int order;
	static std::vector<JFactor> jfactors;
	static std::vector<std::string> jstrings;

	static bool isStringGenerated;
	static void generate_all_Jfactors();

	static void generate_all_Jstrings();

public:

	static void setOrder(int ord);

	static int getNumberByPowers(int powers[Npowers]);

	static std::string getStringByNumber(int k);

	static std::string getStringByPowers(int powers[Npowers]);

	static int getAmountOfPowers();
};

#endif //__J_FACTORS_H__

