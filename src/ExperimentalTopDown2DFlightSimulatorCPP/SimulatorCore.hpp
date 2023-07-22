#include <Vector2.hpp>

class SimulatorCore
{
private:
	SimulatorCore();
public:
	static SimulatorCore instance;

	static godot::String GetBooleanAsString(bool boolean);
};