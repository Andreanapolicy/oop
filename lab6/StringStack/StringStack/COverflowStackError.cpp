#include "COverflowStackError.h"
#include "common_libs.h"

COverflowStackError::COverflowStackError(const std::string& message)
	: std::logic_error(message)
{
}