#include "IPPool.h"
#include <ostream>


bool CIPPool::Push(const CIPv4Address& ip)
{
	if (ip.IsValid())
	{
		m_IPv4Pool.push_back(ip);

		return true;
	}
	
	return false;
}


bool CIPPool::Push(CIPv4Address&& ip)
{
	if (ip.IsValid())
	{
		auto it = m_IPv4Pool.cbegin();

		for (; m_IPv4Pool.cend() != it && ip < *it; ++it);

		m_IPv4Pool.emplace(it, std::move(ip));

		return true;
	}

	return false;
}


CIPPool::ConstIterator CIPPool::begin() const
{
	return m_IPv4Pool.begin();
}


CIPPool::ConstIterator CIPPool::end() const
{
	return m_IPv4Pool.end();
}