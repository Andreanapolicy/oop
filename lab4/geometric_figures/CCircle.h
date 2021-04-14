#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include "common_libs.h"

class CCircle: ISolidShape
{
public:
	CCircle(const CPoint& centralPoint, const double raduis, const uint32_t outlineColor, const uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

	CPoint GetCentralPoint() const;
	double GetRadius() const;

private:
	double const m_pi = 3.14; 

	CPoint m_centralPoint;
	double m_raduis;

	uint32_t m_outlineColor;
	uint32_t m_fillColor;

};
