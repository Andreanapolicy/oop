#pragma once
#include "common_libs.h"

class CCalculator
{
public:
	bool CreateNewVar(const std::string& varName);
	bool SetVarValue(const std::string& varName, const std::string& value);
	double GetVarValue(const std::string& varName) const;
	std::map<std::string, double> GetAllVars() const;

private:
	using Expression = std::pair<char, std::vector<std::string>>;
	std::map<std::string, double> m_memory;
	std::map<std::string, Expression> m_memoryFn;

	bool IsVarAlreadyExist(const std::string& varName) const;
	bool IsValidVar(const std::string& varName) const;
};
