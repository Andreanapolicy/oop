#include "UnableInsertElementError.h"

UnableInsertElementError::UnableInsertElementError(const std::string& message)
	: std::logic_error(message)
{
};
