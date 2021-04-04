#include "CCalculator.h"
#include "common_libs.h"

bool CCalculator::CreateNewVar(const std::string& varName)
{
	if (!IsValidVar(varName) || IsVarAlreadyExist(varName))
	{
		return false;
	}

	m_memory.insert(std::pair<std::string, double>(varName, NAN));
	return true;
}

double CCalculator::GetVarValue(const std::string& varName) const
{
	if (IsVarAlreadyExist(varName))
	{
		return m_memory.find(varName)->second;
	}

	return NAN;
}

std::map<std::string, double> CCalculator::GetAllVars() const
{
	return m_memory;
}

bool CCalculator::SetVarValue(const std::string& varName, const std::string& value)
{
	if (!IsVarAlreadyExist(varName))
	{
		bool varWasCreated = CreateNewVar(varName);
		if (!varWasCreated)
		{
			return false;
		}
	}

	if (std::isdigit(value[0]))
	{
		m_memory.find(varName)->second = std::stod(value);
		return true;
	}
	
	if (IsVarAlreadyExist(value))
	{
		m_memory.find(varName)->second = m_memory.find(value)->second;
	}	

	return false;
}
	
bool CCalculator::IsVarAlreadyExist(const std::string& varName) const
{
	auto it = m_memory.find(varName);

	if (it != m_memory.end())
	{
		return true;
	}

	return false;
}

bool CCalculator::IsValidVar(const std::string& varName) const
{
	if (varName.empty())
	{
		return false;
	}

	if (std::isdigit(varName[0]))
	{
		return false;
	}

    std::regex regex{ R"(\w+)" };

	return std::regex_match(varName, regex);
}
