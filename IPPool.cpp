#include "IPPool.h"


bool CIPPool::Push(const std::string& strData)
{
	bool bResult{ false };
    std::vector<uint8_t> vuiBytes;

	vuiBytes = ValidateData(strData);

	if (vuiBytes.size() == 4)
	{
		bResult = true;

		bool bIsInserted{ false };

		for (auto it = m_lvuiPool.cbegin(); it != m_lvuiPool.cend(); ++it)
		{
			if (vuiBytes > *it)
			{
				m_lvuiPool.emplace(it, vuiBytes);

				bIsInserted = true;
				break;
			}
		}

		if (!bIsInserted)
		{
			m_lvuiPool.emplace_back(vuiBytes);
		}
	}

	return bResult;
}


void CIPPool::ToFilter()
{
	for (auto it = m_lvuiPool.cbegin(); it != m_lvuiPool.cend(); ++it)
	{
		if (it->at(0) == 1)
		{
			m_firstPool.push_back(it);
		}
		else if (it->at(0) == 46)
		{
			if (it->at(1) == 70)
			{
				m_secondPool.push_back(it);
			}
			
			m_thirdPool.push_back(it);
		}
		else if (it->at(1) == 46 || it->at(2) == 46 || it->at(3) == 46)
		{
			m_thirdPool.push_back(it);
		}
	}
}


std::ostream& operator<<(std::ostream& out, const CIPPool& ipPool)
{
	for (const auto& it : ipPool.m_lvuiPool)
	{
		out << static_cast<uint16_t>(it[0]) << "." << 
			static_cast<uint16_t>(it[1]) << "." << 
			static_cast<uint16_t>(it[2]) << "." << 
			static_cast<uint16_t>(it[3]) << "\n";
	}

	ipPool.PrintPool(out, ipPool.m_firstPool);
	ipPool.PrintPool(out, ipPool.m_secondPool);
	ipPool.PrintPool(out, ipPool.m_thirdPool);

	return out;
}


std::vector<uint8_t> CIPPool::ValidateData(const std::string& strData) const
{
	std::vector<uint8_t> vuiBytes;

	std::smatch smResult;
	std::regex rgTemplate{ R"__((\d{1,3}).(\d{1,3}).(\d{1,3}).(\d{1,3})\s.*\s.*)__" };

	if (std::regex_search(strData, smResult, rgTemplate) && smResult.size() == 5)
	{
		int iTemp{ 0 };

		for (size_t i = 1; i <= 4; ++i)
		{
			iTemp = std::stoi(std::string{ smResult[i].first, smResult[i].second });

			if (iTemp < 0 || iTemp > 255)
			{
				throw std::out_of_range{ "Value of one of ip's bytes is too large.\n" };
			}

			vuiBytes.emplace_back(static_cast<uint8_t>(iTemp));
		}
	}

	return vuiBytes;
}


void CIPPool::PrintPool(std::ostream& out, const std::vector<FilterType>& ipPool) const
{
	for (const auto& it : ipPool)
	{
		out << static_cast<uint16_t>(it->at(0)) << "." <<
			static_cast<uint16_t>(it->at(1)) << "." <<
			static_cast<uint16_t>(it->at(2)) << "." <<
			static_cast<uint16_t>(it->at(3)) << "\n";
	}
}