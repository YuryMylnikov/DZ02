#pragma once


#include <list>
#include <array>
#include <string>


#define Octets 4


class CIPv4Address 
{
	bool m_bIsValid;
	std::string m_strIP;
	std::array<uint8_t, Octets> m_auiIP;

public:
	CIPv4Address() : m_bIsValid{ false }, m_auiIP{ 0, 0, 0, 0 } {};
	CIPv4Address(const std::string& strCandidat);
	CIPv4Address(const CIPv4Address& ip);
	CIPv4Address(CIPv4Address&& ip);

	CIPv4Address& operator=(CIPv4Address&& ip);

	bool IsValid() const;
	std::string ToString() const;

	bool operator<(const CIPv4Address& right) const; 

	bool filter(uint8_t byte_1) const;
	bool filter(uint8_t byte_1, uint8_t byte_2) const;
	bool filter_any(uint8_t byte) const;
};