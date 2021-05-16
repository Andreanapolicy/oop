#include "CUrlParsingError.h"
#include "common_libs.h"

CUrlParsingError::CUrlParsingError(const std::string& message)
	: std::invalid_argument(message)
{
}