#include "CCircle.h"
#include "CPoint.h"
#include "CTriangle.h"
#include "common_libs.h"

CCircle::CCircle(const CPoint& centralPoint, const double raduis, const uint32_t outlineColor, const uint32_t fillColor)
	: m_centralPoint(centralPoint)
	, m_raduis(raduis)
	, CFigure(fillColor, outlineColor)
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
	oss << "outline color: #" << std::hex << GetOutlineColor() << " and fill color: #" << std::hex << GetFillColor();

	return oss.str();
}

CPoint CCircle::GetCentralPoint() const
{
	return m_centralPoint;
}

double CCircle::GetRadius() const
{
	return m_raduis;
}