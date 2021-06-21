#include "CFigure.h"

CFigure::CFigure(const uint32_t fillColor, const uint32_t outlineColor)
	: m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

uint32_t CFigure::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CFigure::GetOutlineColor() const
{
	return m_outlineColor;
}