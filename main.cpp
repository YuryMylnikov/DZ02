#include <string>
#include <vector>

#include <iostream>
#include <algorithm>


std::vector<int> SplitString(const std::string& strIP)
{
	std::vector<int> res;

	size_t szBgn{ 0 };
	size_t szEnd{ 0 };

	for (szEnd = strIP.find(".", szBgn); 
		szEnd != std::string::npos; 
		szEnd = strIP.find(".", szBgn))
	{
		res.emplace_back(std::stoi(strIP.substr(szBgn, szEnd - szBgn)));
		szBgn = szEnd + 1;
	}

	res.emplace_back(std::stoi(strIP.substr(szBgn, szEnd - szBgn)));

	return res;
}


int main()
{
	size_t szTabPos{ 0 };
	std::string strIPAddres;
	std::vector<std::vector<int>> strIPAdresses;

	try
	{
		for (std::getline(std::cin, strIPAddres); 
            !std::cin.eof();	
            std::getline(std::cin, strIPAddres))
		{
			szTabPos = strIPAddres.find("\t");

			if (std::string::npos == szTabPos)
			{
				continue;
			}

			try
			{
				strIPAdresses.emplace_back(SplitString(strIPAddres.substr(0, szTabPos)));
			}
			catch (std::invalid_argument&)
			{
				std::cerr << "One of ip's bytes can not be converted to int.\n";
			}
			catch (std::out_of_range&)
			{
				std::cerr << "Value of one of ip's bytes is too large.\n";
			}
			catch (std::exception& ex)
			{
				std::cerr << ex.what() << std::endl;
			}
		}

		std::sort(strIPAdresses.begin(), strIPAdresses.end(), [](auto const& left, auto const& right)
		{
			if (left[0] > right[0])
			{
				return true;
			}
			else if (left[0] == right[0] && left[1] > right[1])
			{
				return true;
			}
			else if (left[0] == right[0] && left[1] == right[1] && left[2] > right[2])
			{
				return true;
			}
			else if (left[0] == right[0] && left[1] == right[1] && left[2] == right[2] && left[3] > right[3])
			{
				return true;
			}

			return false;
		});

		for (const auto& itIPAdress : strIPAdresses)
		{
			for (const auto& itBytes : itIPAdress)
			{
				if (&itBytes != &itIPAdress[0])
				{
					std::cout << ".";
				}

				std::cout << itBytes;
			}

			std::cout << "\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}