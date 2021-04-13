#pragma once
#include "IShape.h"

class ISolidShape: IShape
{
	virtual uint32_t GetFillColor() const = 0;
};
