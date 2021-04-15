#include "CCircle.h"
#include "CPoint.h"
#include "CTriangle.h"
#include "common_libs.h"

CCircle::CCircle(const CPoint& centralPoint, const double raduis, const uint32_t outlineColor, const uint32_t fillColor)
	: m_centralPoint(centralPoint)
	, m_raduis(raduis)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return m_pi * pow(m_raduis, 2);
}

double CCircle::GetPerimeter() const
{
	return m_pi * m_raduis * 2;
}

std::string CCircle::ToString() const
{
	std::string text = "circle with center (" + std::to_string(m_centralPoint.x) + ", " + std::to_string(m_centralPoint.y) + "), radius " + std::to_string(m_raduis) + ", outline color: " + std::to_string(m_outlineColor) + " and fill color: " + std::to_string(m_fillColor);

	return text;
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCentralPoint() const
{
	return m_centralPoint;
}

double CCircle::GetRadius() const
{
	return m_raduis;
}