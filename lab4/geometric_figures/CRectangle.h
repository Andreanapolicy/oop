#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include "common_libs.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint& topLeftPoint, const double width, const double height, const uint32_t outlineColor, const uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;

	CPoint GetTopLeftPoint() const;
	CPoint GetBottomRightPoint() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_topLeftPoint;
	double m_width;
	double m_height;

	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
