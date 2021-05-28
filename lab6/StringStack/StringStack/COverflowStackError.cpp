#include "COverflowStackError.h"

COverflowStackError::COverflowStackError(const std::string& message)
	: std::logic_error(message)
{
}