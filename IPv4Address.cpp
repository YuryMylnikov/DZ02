#include "IPv4Address.h"


#include "Tokenizer.h"


CIPv4Address::CIPv4Address(const std::string& strCandidat) : m_auiIP{ 0, 0, 0, 0 }, m_bIsValid{ true }
{
	int iByte{ 0 };
	size_t szInd{ 0 };
	size_t szFailInd{ 0 };
	
	try
	{
		m_strIP = strCandidat.substr(0, strCandidat.find('\t'));

		CTokenizer tok{ m_strIP };

		for (std::string strByte = tok.GetToken(".");
			!strByte.empty();
			strByte = tok.GetToken("."))
		{
			iByte = std::stoi(strByte, &szFailInd);

			//Byte format
			if (strByte.size() != szFailInd || iByte < 0 || iByte > 255)
			{
				throw std::invalid_argument{ "Invalid byte format" };
			}

			m_auiIP.at(szInd++) = static_cast<uint8_t>(iByte);
		}

		if (tok.ReachedTheEnd() != std::string::npos || szInd != Octets)
		{
			throw std::logic_error{ "Invalid ip format" };
		}
	}
	catch (const std::exception&)
	{
		m_auiIP = { 0, 0, 0, 0 };
		m_bIsValid = false;
	}
}


CIPv4Address::CIPv4Address(const CIPv4Address& ip)
{
	m_bIsValid = ip.m_bIsValid;
	m_auiIP = ip.m_auiIP;
	m_strIP = ip.m_strIP;
}


CIPv4Address::CIPv4Address(CIPv4Address&& ip)
{
	m_bIsValid = ip.m_bIsValid;
	m_strIP = std::move(ip.m_strIP);
	m_auiIP = std::move(ip.m_auiIP);
}


CIPv4Address& CIPv4Address::operator=(CIPv4Address&& ip)
{
	m_bIsValid = ip.m_bIsValid;
	m_auiIP = std::move(ip.m_auiIP);

	return *this;
}


bool CIPv4Address::IsValid() const
{
	return m_bIsValid;
}


std::string CIPv4Address::ToString() const
{
	return m_strIP;
}


bool CIPv4Address::operator<(const CIPv4Address& right) const
{
	return m_auiIP < right.m_auiIP;
}


bool CIPv4Address::filter(uint8_t byte_1) const
{
	return m_auiIP[0] == byte_1;
}


bool CIPv4Address::filter(uint8_t byte_1, uint8_t byte_2) const
{
	return m_auiIP[0] == byte_1 && m_auiIP[1] == byte_2;
}


bool CIPv4Address::filter_any(uint8_t byte) const
{
	return m_auiIP[0] == byte || m_auiIP[1] == byte || m_auiIP[2] == byte || m_auiIP[3] == byte;
}