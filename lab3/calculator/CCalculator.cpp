#include "CCalculator.h"
#include "common_libs.h"

bool CCalculator::CreateNewVar(const std::string& varName)
{
	if (!IsValidName(varName) || IsVarAlreadyExist(varName))
	{
		return false;
	}

	m_memory.insert(std::pair<std::string, double>(varName, NAN));
	return true;
}

double CCalculator::GetIdentifierValue(const std::string& identifierName) const
{
	if (IsVarAlreadyExist(identifierName))
	{
		return m_memory.find(identifierName) != m_memory.end() ? m_memory.find(identifierName)->second : CalculateFunctionValue(m_memoryFn.find(identifierName)->second);
	}

	return NAN;
}

std::map<std::string, double> CCalculator::GetAllVars() const
{
	return m_memory;
}

std::map<std::string, CCalculator::Expression> CCalculator::GetAllFunctions() const
{
	return m_memoryFn;
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

bool CCalculator::SetFunctionValue(const Function& function)
{
	if (IsVarAlreadyExist(function.first))
	{
		return false;
	}

	if (!IsValidName(function.first))
	{
		return false;
	}
	
	if (IsValidFunction(function))
	{
		m_memoryFn.insert(function);
		
		return true;
	}

	return false;
}
	
bool CCalculator::IsValidFunction(const Function& function) const
{
	auto functionName = function.first;
	auto expression = function.second;

	if (expression.second.size() == 0 || expression.second.size() > 2)
	{
		return false;
	}

	if (expression.first == ' ')
	{
		if (expression.second.size() > 1)
		{
			return false;
		}

		if (isValidOperands(functionName, expression.second))
		{
			return true;
		}

		return true;
	}

	auto it = std::find(m_operators.begin(), m_operators.end(), expression.first);

	if (it == m_operators.end() || expression.second.size() != 2)
	{
		return false;
	}
	
	if (isValidOperands(functionName, expression.second))
	{
		return true;
	}
	
	return false;
}

bool CCalculator::isValidOperands(const std::string& functionName, const std::vector<std::string>& operands) const
{
	if (operands.size() == 1)
	{
		return (operands[0] != functionName) && IsVarAlreadyExist(operands[0]);
	}

	if (operands.size() == 2)
	{
		return (operands[0] != functionName || operands[1] != functionName) && IsVarAlreadyExist(operands[0]) && IsVarAlreadyExist(operands[1]);
	}

	return false;
}


bool CCalculator::IsVarAlreadyExist(const std::string& varName) const
{
	auto itVars = m_memory.find(varName);

	if (itVars != m_memory.end())
	{
		return true;
	}

	auto itFn = m_memoryFn.find(varName);

	if (itFn != m_memoryFn.end())
	{
		return true;
	}

	return false;
}

bool CCalculator::IsValidName(const std::string& varName) const
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

double CCalculator::CalculateFunctionValue(const Expression& expression) const
{
	return NAN;
}