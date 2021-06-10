#pragma once
#include <stdexcept>

class UnableInsertElementError : public std::logic_error
{
public:
	UnableInsertElementError(const std::string& message);
};
