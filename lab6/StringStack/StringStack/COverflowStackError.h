#pragma once
#include "common_libs.h"

class COverflowStackError: std::logic_error
{
public:
	COverflowStackError(const std::string& message);
};
