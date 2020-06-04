#include "Tokenizer.h"


std::string CTokenizer::GetToken(const std::string& strDelim)
{
	if (std::string::npos == m_szEnd)
	{
		return std::string{};
	}
	
	m_szBgn = m_strString.find_first_not_of(strDelim, m_szEnd);

	if (std::string::npos == m_szBgn)
	{
		return std::string{};
	}

	m_szEnd = m_strString.find_first_of(strDelim, m_szBgn);

	return m_strString.substr(m_szBgn, m_szEnd - m_szBgn);
}


void CTokenizer::operator=(std::string&& strRight)
{
	m_szBgn = 0;
	m_szEnd = 0;
	m_strString = std::move(strRight);
}


size_t CTokenizer::ReachedTheEnd() const
{
	return m_szEnd;
}