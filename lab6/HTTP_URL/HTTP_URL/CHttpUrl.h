#pragma once
#include "common_libs.h"

enum class Protocol
{
	HTTP,
	HTTPS
};

const std::map<Protocol, unsigned short> DefaultPorts{
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 442 }
};

class CHttpUrl
{
public:
	CHttpUrl(const std::string& url);

	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP);

	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;

	std::string GetDomain() const;

	std::string GetDocument() const;

	Protocol GetProtocol() const;

	unsigned short GetPort() const;

	static std::string FromProtocolToString(const Protocol& protocol);

private:
	void ParseURL(const std::string& url);

	static std::string ParseDocument(const std::string& document);

	static Protocol ParseProtocol(const std::string& protocol);

	static unsigned short ParsePort(const std::string& port, const Protocol& protocol);

	static unsigned short GetDefaultPort(const Protocol& protocol);

	static std::string GetStringInLowerCase(const std::string& line);

	std::string m_domain;

	std::string m_document;
	
	Protocol m_protocol;

	unsigned short m_port;
};
