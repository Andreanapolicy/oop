#pragma once
#include "CPoint.h"
#include "CFigure.h"
#include "common_libs.h"

class CTriangle : public CFigure
{
public:
	CTriangle(const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex, const uint32_t outlineColor, const uint32_t fillColor);

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	CPoint GetVertex1() const;

	CPoint GetVertex2() const;

	CPoint GetVertex3() const;

private:
	CPoint m_firstVertex;

	CPoint m_secondVertex;

	CPoint m_thirdVertex;
};
