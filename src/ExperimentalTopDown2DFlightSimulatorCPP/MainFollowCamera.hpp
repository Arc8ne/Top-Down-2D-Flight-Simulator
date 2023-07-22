#pragma once

#include <map>

#include <Godot.hpp>

#include <Camera2D.hpp>

#include <InputEvent.hpp>

#include <InputEventKey.hpp>

#include <GlobalConstants.hpp>

#include <Sprite.hpp>

#include <Label.hpp>

#include <Vector2.hpp>

#include <VBoxContainer.hpp>

#include <Viewport.hpp>

#include <Transform2D.hpp>

#include <StyleBox.hpp>

#include <InputEventMouseMotion.hpp>

#include <InputEventMouseButton.hpp>

#include "SimulatorCore.hpp"

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

	double altitudeChangeRate = 0;

	std::map<int, bool> keyToPressedStatusMap = std::map<int, bool>();

	godot::Sprite* aircraftSpritePtr = nullptr;

	godot::Sprite* aircraftShadowPtr = nullptr;

	godot::VBoxContainer* hudVBoxContainerPtr = nullptr;

	godot::Label* airspeedLabelPtr = nullptr;

	godot::Label* altitudeLabelPtr = nullptr;

	godot::Vector2 shadowOffset = godot::Vector2(0, 0);

	godot::Color redColor = godot::Color(255, 0, 65, 1);

	godot::Color whiteColor = godot::Color(255, 255, 255, 1);

	int lowAltitude = 101;

	void RegulateVelocity();

	void RegulateAltitude();

	void UpdateAirspeedLabel();

	void UpdateAltitudeLabel();

	void UpdateShadowBasedOnAltitude();

	void UpdateShadowBasedOnRotation();

	void UpdateHUDBasedOnCameraZoom();

	godot::Vector2 GetLift();

	void OnInputMouseMotion(godot::InputEventMouseMotion* inputEventMouseMotionPtr);

	void OnInputMouseButton(godot::InputEventMouseButton* inputEventMouseButtonPtr);
public:
	static void _register_methods();

	void _init();

	void _ready();

	void _input(godot::InputEvent* inputEventPtr);

	void _physics_process(float delta);
};
