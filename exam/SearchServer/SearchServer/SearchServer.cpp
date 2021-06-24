#include "SearchServer.h"

SearchServer::SearchServer()
{
	m_docs = {};
	m_docsCount = 0;
}

int SearchServer::GetDocsCount() const
{
	return m_docsCount;
}