#include "CCar.h"
#include "common_libs.h"

bool CCar::TurnOnEngine()
{
	m_isEngineTurn = true;
	return m_isEngineTurn;
}

bool CCar::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_isEngineTurn = false;
	}
	
	return !m_isEngineTurn;
}

bool CCar::SetSpeed(int newSpeed)
{
	std::vector speedInterval = GetSpeedIntervalForGear(m_gear);
	int currentGear = GetGear();
	int minSpeed = speedInterval[0];
	int maxSpeed = speedInterval[1];
	newSpeed = abs(newSpeed);

	if (!m_isEngineTurn)
	{
		return false;
	}

	if (newSpeed == 0 && currentGear == 0)
	{
		m_needStop = false;
	}

	if (currentGear == 0 && newSpeed <= m_speed)
	{
		m_speed = newSpeed;
		SetDirection();
		return true;
	}

	if (currentGear != 0 && minSpeed <= newSpeed && newSpeed <= maxSpeed)
	{
		m_speed = newSpeed;
		SetDirection();
		return true;
	}

	return false;
}

bool CCar::SetGear(int newGear)
{
	if (newGear < -1 || newGear > 5)
	{
		return false;
	}

	int currentGear = GetGear();

	if (newGear == currentGear)
	{
		return true;
	}

	if (newGear == -1)
	{
		if (m_speed == 0)
		{
			m_gear = newGear;
			SetDirection();
			return true;
		}

		return false;
	}

	if (currentGear == -1 && newGear == 0)
	{
		m_gear = newGear;
		SetDirection();
		m_needStop = m_speed != 0;
		return true;
	}

	if (currentGear == -1 && newGear == 1 && m_speed == 0)
	{
		m_gear = newGear;
		SetDirection();
		return true;
	}

	std::vector speedInterval = GetSpeedIntervalForGear(newGear);
	int minSpeed = speedInterval[0];
	int maxSpeed = speedInterval[1];

	if (currentGear != -1 && minSpeed <= m_speed && m_speed <= maxSpeed && !m_needStop)
	{
		m_gear = newGear;
		SetDirection();
		return true;
	}

	return false;
}

void CCar::SetDirection()
{
	if (m_speed == 0)
	{
		m_direction = Direction::ON_THE_SPOT;
		return;
	}

	if (m_gear >= 0)
	{
		m_direction = Direction::FORWARD;
		return;
	}

	if (m_gear == -1)
	{
		m_direction = Direction::BACKWARD;
		return;
	}

	return;
}

bool CCar::IsEngineTurn() const
{
	return m_isEngineTurn;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

SpeedIntervalForGears CCar::InitSpeedIntervalForGears() const
{
	SpeedIntervalForGears speedIntervalForGears;
	speedIntervalForGears[-1] = { 0, 20 };
	speedIntervalForGears[0] = { 0, 150 };
	speedIntervalForGears[1] = { 0, 30 };
	speedIntervalForGears[2] = { 20, 50 };
	speedIntervalForGears[3] = { 30, 60 };
	speedIntervalForGears[4] = { 40, 90 };
	speedIntervalForGears[5] = { 50, 150 };

	return speedIntervalForGears;
}

SpeedInterval CCar::GetSpeedIntervalForGear(int gear) const
{
	return m_speedIntervalForGears.find(gear)->second;
}