#pragma once
#include "../ICanvas.h"
#include <SFML/Graphics.hpp>

class CMockCanvas : public ICanvas
{
public:
	enum class Notification
	{
		DrawLine,
		DrawPolygon,
		DrawCircle,
	};

	void DrawLine(CPoint firstPoint, CPoint secondPoint, uint32_t outlineColor) override;

	void DrawPolygon(std::vector<CPoint> points, uint32_t outlineColor, uint32_t fillColor) override;

	void DrawCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor) override;

	std::vector<Notification> GetNotifications() const;

private:
	std::vector<Notification> m_notifications;
};