#include "CRectangle.h"
#include "CPoint.h"
#include "CTriangle.h"
#include "common_libs.h"

CRectangle::CRectangle(const CPoint& topLeftPoint, const double width, const double height, const uint32_t outlineColor, const uint32_t fillColor)
	: m_topLeftPoint(topLeftPoint)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
	std::ostringstream oss;

	oss << std::fixed << std::setprecision(1);
	oss << "rectangle with top left point ";
	oss << "(" << m_topLeftPoint.x << ", " << m_topLeftPoint.y << "), ";
	oss << "width: " << m_width << " and height: " << m_height << " ";
	oss << "outline color: #" << std::hex << m_outlineColor << " and fill color: #" << std::hex << m_fillColor;

	return oss.str();
}

CPoint CRectangle::GetTopLeftPoint() const
{
	return m_topLeftPoint;
}

CPoint CRectangle::GetBottomRightPoint() const
{
	CPoint bottomRightPoint(m_topLeftPoint.x + m_width, m_topLeftPoint.y - m_height);
	
	return bottomRightPoint;
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
