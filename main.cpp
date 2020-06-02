#include <fstream>
#include <iostream>

#include "IPPool.h"


void PrintPool(const CIPPool& pool)
{
	for (const auto& it : pool)
	{
		std::cout << it.ToString() << std::endl;
	}
}


int main()
{
	CIPPool pool{};
	CIPPool pool_first{};
	CIPPool pool_second{};
	CIPPool pool_third{};
	
	//std::fstream in("in.tsv", std::ios_base::in);

	//for (std::string strInput{}; std::getline(in, strInput);)
	for (std::string strInput{}; std::getline(std::cin, strInput);)
	{
		pool.Push(strInput);
	}

	for (const auto& it : pool)
	{
		if (it.filter(1))
		{
			pool_first.Push(it);
		}
		else if (it.filter(46, 70))
		{
			pool_second.Push(it);
		}

		if (it.filter_any(46))
		{
			pool_third.Push(it);
		}

		std::cout << it.ToString() << "\n";
	}

	PrintPool(pool_first);
	PrintPool(pool_second);
	PrintPool(pool_third);

	return 0;
}