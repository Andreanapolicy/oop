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
	return M_PI * pow(m_raduis, 2);
}

double CCircle::GetPerimeter() const
{
	return M_PI * m_raduis * 2;
}

std::string CCircle::ToString() const
{
	std::ostringstream oss;

	oss << std::fixed << std::setprecision(1);
	oss << "circle with center ";
	oss << "(" << m_centralPoint.x << ", " << m_centralPoint.y << "), ";
	oss << "radius: " << m_raduis << ", ";
	oss << "outline color: #" << std::hex << m_outlineColor << " and fill color: #" << std::hex << m_fillColor;

	return oss.str();
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