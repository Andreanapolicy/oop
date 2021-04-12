#include "CLineSegment.h"
#include "CPoint.h"
#include "common_libs.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, const uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_startPoint.y - m_endPoint.y, 2) + pow(m_startPoint.x - m_endPoint.x, 2));
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
