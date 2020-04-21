#include "IPPool.h"


#include <fstream>


int main()
{
	CIPPool ipPool;
	std::string strInputData;

	/*std::fstream in("in.tsv", std::ios_base::in);
	std::fstream out("out2.txt", std::ios_base::out);*/

	try
	{
		/*for (std::getline(in, strInputData);
			!in.eof();
			std::getline(in, strInputData))*/
		for (std::getline(std::cin, strInputData);
			!std::cin.eof();
			std::getline(std::cin, strInputData))
		{
			try
			{
				ipPool.Push(strInputData);
			}
			catch (std::invalid_argument&)
			{
				std::cerr << "One of ip's bytes can not be converted to int.\n";
			}
			catch (std::exception& ex)
			{
				std::cerr << ex.what() << std::endl;
			}
		}

		ipPool.ToFilter();
		std::cout << ipPool;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}