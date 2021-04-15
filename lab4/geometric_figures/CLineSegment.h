#pragma once

#include "CPoint.h"
#include "IShape.h"
#include "common_libs.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, const uint32_t outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	std::string ToString() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;

	uint32_t m_outlineColor;
};
