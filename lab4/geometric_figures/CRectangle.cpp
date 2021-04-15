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
	std::string text = "rectangle with top left point (" + std::to_string(m_topLeftPoint.x) + ", " + std::to_string(m_topLeftPoint.y) + "), width " + std::to_string(m_width) + " and height " + std::to_string(m_height) + ", outline color: " + std::to_string(m_outlineColor) + " and fill color: " + std::to_string(m_fillColor);

	return text;
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
