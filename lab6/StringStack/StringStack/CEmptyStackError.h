#pragma once
#include "common_libs.h"

class CEmptyStackError : std::logic_error
{
public:
	CEmptyStackError(const std::string& message);
};
