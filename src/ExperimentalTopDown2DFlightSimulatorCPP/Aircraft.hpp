#include <String.hpp>

#include <Vector2.hpp>

#include <Sprite.hpp>

/*
Physics goals:
- Airspeed should affect altitude.
- Pitch, roll and altitude should not affect airspeed.
*/

class Aircraft
{
private:
	godot::String name = "";

	godot::Vector2 velocity = godot::Vector2(0, 0);

	double area = 0;

	double airPressure = 1.0;

	double liftCoefficient = 1.0;

	double dragCoefficient = 1.0;

	double angleOfAttack = 0.0;

	godot::Sprite* aircraftSpritePtr = nullptr;
public:
	Aircraft(godot::Sprite* aircraftSpritePtr);

	double GetLift();

	double GetDrag();
};