#pragma once


#include <string>


class CTokenizer
{
	size_t m_szBgn;
	size_t m_szEnd;

	std::string m_strString;

public:
	CTokenizer(const std::string& strData) : m_strString{ strData }, m_szBgn{ 0 }, m_szEnd{ 0 } {};

	void operator=(std::string&& strRight);
	size_t ReachedTheEnd() const;

	std::string GetToken(const std::string& strDelim);
};