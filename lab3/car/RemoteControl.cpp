#include "RemoteControl.h"
#include "common_libs.h"

RemoteControl::RemoteControl(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ 
		{ "EngineOn", [this](int args) { return EngineOn(args); } },  
		{ "EngineOff", [this](int args) { return EngineOff(args); } },
		{ "SetGear", [this](int args) { return SetGear(args); } },
		{ "SetSpeed", [this](int args) { return SetSpeed(args); } },
		{ "Info", [this](int args) { return Info(args); } } })
{
}

bool RemoteControl::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);

	std::istringstream stream(commandLine);

	std::string action;
	int args;
	std::getline(stream, action, ' ');
	args = stream >> args ? args : 0;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(args);
	}

	return false;
}

bool RemoteControl::EngineOn(int /*args*/)
{
	m_car.TurnOnEngine();
	m_output << "Engine is turn on" << std::endl;

	return true;
}

bool RemoteControl::EngineOff(int /*args*/)
{
	m_car.TurnOffEngine();
	m_output << "Engine is turn off" << std::endl;

	return true;
}

bool RemoteControl::SetGear(int args)
{
	if (!m_car.SetGear(args))
	{
		m_output << "There is some problems with setting new gear" << std::endl;
		return true;
	}

	m_output << "Set gear " << args << " succeed" << std::endl;

	return true;
}

bool RemoteControl::SetSpeed(int args)
{
	if (!m_car.SetSpeed(args))
	{
		m_output << "There is some problems with setting new speed" << std::endl;
		return true;
	}

	m_output << "Set speed " << args << " succeed" << std::endl;

	return true;
}

bool RemoteControl::Info(int /*args*/)
{
	std::string engineState = m_car.IsEngineTurn() ? "on" : "off";
	m_output << "Engine is: " << engineState << std::endl;
	m_output << "Speed: " << std::to_string(m_car.GetSpeed()) << std::endl;
	m_output << "Gear: " << std::to_string(m_car.GetGear()) << std::endl;

	std::string convertedDirection;
	switch (m_car.GetDirection())
	{
	case Direction::FORWARD:
		convertedDirection = "forward";
		break;
	case Direction::BACKWARD:
		convertedDirection = "backward";
		break;
	case Direction::ON_THE_SPOT:
		convertedDirection = "on the spot";
		break;
	}

	m_output << "Direction: " << convertedDirection << std::endl;

	return true;
}
