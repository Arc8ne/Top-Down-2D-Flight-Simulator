#pragma once

#include <map>

#include <Godot.hpp>

#include <Camera2D.hpp>

#include <InputEvent.hpp>

#include <InputEventKey.hpp>

#include <GlobalConstants.hpp>

#include <Sprite.hpp>

#include <Label.hpp>

class MainFollowCamera : public godot::Camera2D
{
	GODOT_CLASS(MainFollowCamera, godot::Camera2D)
private:
	int acceleration = 1;

	int deceleration = 1;

	int turnRate = 50;

	int maxVelocity = 200;

	int velocity = 0;

	int altitude = 0;

	int ascentRate = 1;

	int descentRate = 1;

	std::map<int, bool> keyToPressedStatusMap = std::map<int, bool>();

	godot::Sprite* aircraftSpritePtr = nullptr;

	godot::Sprite* aircraftShadowPtr = nullptr;

	godot::Label* airspeedLabelPtr = nullptr;

	godot::Label* altitudeLabelPtr = nullptr;

	void RegulateVelocity();

	void RegularAltitude();

	void UpdateAirspeedLabel();

	void UpdateAltitudeLabel();

	void UpdateShadowBasedOnAltitude();

	void UpdateShadowBasedOnRotation();
public:
	static void _register_methods();

	void _init();

	void _ready();

	void _input(godot::InputEvent* inputEventPtr);

	void _physics_process(float delta);
};
