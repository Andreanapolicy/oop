#pragma once
#include "common_libs.h"
#include "CCar.h"

class CRemoteControl
{
public:
	CRemoteControl(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool EngineOn(int args);
	bool EngineOff(int args);
	bool SetGear(int args);
	bool SetSpeed(int args);
	bool Info(int args) const;

private:
	using Handler = std::function<bool(int args)>;

	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
