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

void SearchServer::AddDoc(const std::string& doc)
{
	if (doc.empty())
	{
		return; // exception?
	}

	m_docs.insert(std::pair<int, std::string>(m_docsCount, doc));

	m_docsCount++;
}