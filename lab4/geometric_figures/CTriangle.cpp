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
	std::string text = "triangle with vertices (" + std::to_string(m_firstVertex.x) + ", " + std::to_string(m_firstVertex.y) + ") (" + std::to_string(m_secondVertex.x) + ", " + std::to_string(m_secondVertex.y) + ") (" + std::to_string(m_thirdVertex.x) + ", " + std::to_string(m_thirdVertex.y) + "), outline color: " + std::to_string(m_outlineColor) + " and fill color: " + std::to_string(m_fillColor);

	return text;
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