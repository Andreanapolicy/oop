#pragma once
#include <map>
#include <string>

class SearchServer
{
public:
	SearchServer();

	int GetDocsCount() const;
	
	void AddDoc(const std::string& doc);

private:
	std::map<int, std::string> m_docs;

	int m_docsCount;
};
