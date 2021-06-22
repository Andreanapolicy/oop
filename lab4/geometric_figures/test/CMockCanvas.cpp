#include "CMockCanvas.h"

void CMockCanvas::DrawLine(CPoint firstPoint, CPoint secondPoint, uint32_t outlineColor)
{
	m_notifications.push_back(Notification::DrawLine);
}

void CMockCanvas::DrawPolygon(std::vector<CPoint> points, uint32_t outlineColor, uint32_t fillColor)
{
	m_notifications.push_back(Notification::DrawPolygon);
}

void CMockCanvas::DrawCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
	m_notifications.push_back(Notification::DrawCircle);
}

std::vector<CMockCanvas::Notification> CMockCanvas::GetNotifications() const
{
	return m_notifications;
}
