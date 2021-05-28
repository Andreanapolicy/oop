#pragma once
#include <stdexcept>
#include <string>

class COverflowStackError: std::logic_error
{
public:
	COverflowStackError(const std::string& message);
};
