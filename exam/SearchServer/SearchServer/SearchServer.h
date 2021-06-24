#pragma once
#include <map>
#include <string>

class SearchServer
{
public:
	SearchServer();

	int GetDocsCount() const;

private:
	std::map<int, std::string> m_docs;

	int m_docsCount;
};
