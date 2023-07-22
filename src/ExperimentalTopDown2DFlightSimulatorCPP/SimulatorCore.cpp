#include "SimulatorCore.hpp"

SimulatorCore::SimulatorCore()
{

}

godot::String SimulatorCore::GetBooleanAsString(bool boolean)
{
	if (boolean == true)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}
