#include "CEmptyStackError.h"
#include "common_libs.h"

CEmptyStackError::CEmptyStackError(const std::string& message)
	: std::logic_error(message)
{
}