#include "CTriangle.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "common_libs.h"

CTriangle::CTriangle(const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex, const uint32_t outlineColor, const uint32_t fillColor)
	: m_firstVertex(firstVertex)
	, m_secondVertex(secondVertex)
	, m_thirdVertex(thirdVertex)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	return CTriangle::IsValidTriangle(m_firstVertex, m_secondVertex, m_thirdVertex);
}

CPoint CTriangle::GetVertex1() const
{
	return m_firstVertex;
}

std::string CTriangle::ToString() const
{
	std::ostringstream oss;

	oss << std::fixed << std::setprecision(1);
	oss << "triangle with points ";
	oss << "(" << m_firstVertex.x << ", " << m_firstVertex.y << "), ";
	oss << "(" << m_secondVertex.x << ", " << m_secondVertex.y << "), ";
	oss << "(" << m_thirdVertex.x << ", " << m_thirdVertex.y << "), ";
	oss << "outline color: #" << std::hex << m_outlineColor << " and fill color: #" << std::hex << m_fillColor;

	return oss.str();
}

CPoint CTriangle::GetVertex2() const
{
	return m_secondVertex;
}

CPoint CTriangle::GetVertex3() const
{
	return m_thirdVertex;
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

double CTriangle::GetPerimeter() const
{
	CLineSegment firstLine(m_firstVertex, m_secondVertex, 0xffffff);
	double firstLineLenght = firstLine.GetPerimeter();

	CLineSegment secondLine(m_firstVertex, m_thirdVertex, 0xffffff);
	double secondLineLenght = secondLine.GetPerimeter();

	CLineSegment thirdLine(m_thirdVertex, m_secondVertex, 0xffffff);
	double thirdLineLenght = thirdLine.GetPerimeter();

	return firstLineLenght + secondLineLenght + thirdLineLenght;
}

double CTriangle::IsValidTriangle(const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex)
{
	CLineSegment firstLine(firstVertex, secondVertex, 0xffffff);
	double firstLineLenght = firstLine.GetPerimeter();

	CLineSegment secondLine(firstVertex, thirdVertex, 0xffffff);
	double secondLineLenght = secondLine.GetPerimeter();

	CLineSegment thirdLine(thirdVertex, secondVertex, 0xffffff);
	double thirdLineLenght = thirdLine.GetPerimeter();

	if (firstLineLenght == 0 || secondLineLenght == 0 || thirdLineLenght == 0)
	{
		return 0;
	}

	double halfPerimeter = (firstLineLenght + secondLineLenght + thirdLineLenght) / 2;

	return sqrt(halfPerimeter * (halfPerimeter - firstLineLenght) * (halfPerimeter - secondLineLenght) * (halfPerimeter - thirdLineLenght));
}