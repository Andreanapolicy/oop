#pragma once
#include "CPoint.h"
#include "CFigure.h"
#include "common_libs.h"

class CCircle final : public CFigure
{
public:
	CCircle(const CPoint& centralPoint, const double raduis, const uint32_t outlineColor, const uint32_t fillColor);
	
	double GetArea() const override;
	
	double GetPerimeter() const override;
	
	std::string ToString() const override;

	CPoint GetCentralPoint() const;
	
	double GetRadius() const;

private:
	double const M_PI = 3.14; 

	CPoint m_centralPoint;
	
	double m_raduis;
};
