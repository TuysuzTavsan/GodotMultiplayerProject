#include <locator.h>

void Locator::Init()
{
	m_parser = &m_nullParser;
}


IParser& Locator::GetParser()
{
	return *m_parser;
}

void Locator::ProvideParser(IParser* parser)
{
	if (!parser)
	{
		//fall back to null service.
		m_parser = &m_nullParser;
	}
	else
	{
		m_parser = parser;
	}
}

NULLParser Locator::m_nullParser;
IParser* Locator::m_parser{ nullptr };