#pragma once
#include "common_libs.h"

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
};