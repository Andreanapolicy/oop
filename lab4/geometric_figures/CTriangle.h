#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include "common_libs.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex, const uint32_t outlineColor, const uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	double static IsValidTriangle(const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex);

private:
	CPoint m_firstVertex;
	CPoint m_secondVertex;
	CPoint m_thirdVertex;

	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
