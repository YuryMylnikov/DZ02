#pragma once


#include <vector>
#include <list>
#include <vector>
#include <string>


#include <regex>
#include <iostream>


class CIPPool
{
	std::list<std::vector<uint8_t>>  m_lvuiPool;

	using FilterType = decltype(m_lvuiPool.cbegin());

	std::vector<FilterType>  m_firstPool;
	std::vector<FilterType>  m_secondPool;
	std::vector<FilterType>  m_thirdPool;

public:
	bool Push(const std::string& strData);
	void ToFilter();

	friend std::ostream& operator<<(std::ostream& out, const CIPPool& ipPool);


private:
	std::vector<uint8_t> ValidateData(const std::string& strData) const;
	void PrintPool(std::ostream& out, const std::vector<FilterType>& ipPool) const;
};