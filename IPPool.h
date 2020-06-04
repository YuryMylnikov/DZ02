#pragma once

#include "IPv4Address.h"

class CIPPool
{
	std::list<CIPv4Address> m_IPv4Pool;

	using ConstIterator = std::list<CIPv4Address>::const_iterator;

public:
	bool Push(const CIPv4Address& ip);
	bool Push(CIPv4Address&& ip);

	ConstIterator begin() const;
	ConstIterator end() const;
};