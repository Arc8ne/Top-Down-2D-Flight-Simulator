#include "MainFollowCamera.hpp"

void MainFollowCamera::RegulateVelocity()
{
	if (this->velocity >= 0)
	{
		if (this->velocity > this->maxVelocity)
		{
			this->velocity = this->maxVelocity;
		}
	}
	else
	{
		this->velocity = 0;
	}
}

void MainFollowCamera::RegularAltitude()
{
	if (this->altitude < 0)
	{
		this->altitude = 0;
	}
}

void MainFollowCamera::UpdateAirspeedLabel()
{
	this->airspeedLabelPtr->set_text(
		"Airspeed: " + godot::String::num(this->velocity) + (godot::String)" kts"
	);
}

void MainFollowCamera::UpdateAltitudeLabel()
{
	this->altitudeLabelPtr->set_text(
		"Altitude: " + godot::String::num(this->altitude) + (godot::String)" ft"
	);
}

void MainFollowCamera::UpdateShadowBasedOnAltitude()
{
	this->aircraftShadowPtr->set_position(
		this->aircraftSpritePtr->get_position() + godot::Vector2(
			this->altitude * -0.2,
			this->altitude * 0.2
		)
	);
}

void MainFollowCamera::UpdateShadowBasedOnRotation()
{
	this->aircraftShadowPtr->set_rotation(
		this->aircraftSpritePtr->get_rotation()
	);
}

void MainFollowCamera::_register_methods()
{
	godot::register_method("_ready", &MainFollowCamera::_ready);

	godot::register_method("_input", &MainFollowCamera::_input);

	godot::register_method("_physics_process", &MainFollowCamera::_physics_process);
}

void MainFollowCamera::_init()
{

}

void MainFollowCamera::_ready()
{
	this->aircraftSpritePtr = godot::Object::cast_to<godot::Sprite>(
		this->get_node("AircraftSprite")
	);

	this->aircraftShadowPtr = godot::Object::cast_to<godot::Sprite>(
		this->get_node("AircraftShadowSprite")
	);

	this->airspeedLabelPtr = godot::Object::cast_to<godot::Label>(
		this->get_node("HUDCanvasLayer/HUDVBoxContainer/AirspeedLabel")
	);

	this->altitudeLabelPtr = godot::Object::cast_to<godot::Label>(
		this->get_node("HUDCanvasLayer/HUDVBoxContainer/AltitudeLabel")
	);

	this->UpdateAirspeedLabel();

	this->UpdateAltitudeLabel();
}

void MainFollowCamera::_input(godot::InputEvent* inputEventPtr)
{
	if (inputEventPtr->is_class("InputEventKey") == true)
	{
		godot::InputEventKey* inputEventKeyPtr = godot::Object::cast_to<godot::InputEventKey>(inputEventPtr);
	
		this->keyToPressedStatusMap[inputEventKeyPtr->get_scancode()] = inputEventPtr->is_pressed();
	}
}

void MainFollowCamera::_physics_process(float delta)
{
	if (this->keyToPressedStatusMap[godot::GlobalConstants::KEY_PAGEUP] == true)
	{
		this->velocity += this->acceleration;

		this->RegulateVelocity();

		this->UpdateAirspeedLabel();
	}
	else if (this->keyToPressedStatusMap[godot::GlobalConstants::KEY_PAGEDOWN] == true)
	{
		this->velocity -= this->deceleration;

		this->RegulateVelocity();

		this->UpdateAirspeedLabel();
	}
	
	if (this->keyToPressedStatusMap[godot::GlobalConstants::KEY_A] == true)
	{
		this->aircraftSpritePtr->set_rotation_degrees(
			this->aircraftSpritePtr->get_rotation_degrees() - this->turnRate * delta
		);

		this->UpdateShadowBasedOnRotation();
	}
	else if (this->keyToPressedStatusMap[godot::GlobalConstants::KEY_D] == true)
	{
		this->aircraftSpritePtr->set_rotation_degrees(
			this->aircraftSpritePtr->get_rotation_degrees() + this->turnRate * delta
		);

		this->UpdateShadowBasedOnRotation();
	}

	if (this->keyToPressedStatusMap[godot::GlobalConstants::KEY_W] == true)
	{
		this->altitude += this->ascentRate;

		this->UpdateAltitudeLabel();

		this->UpdateShadowBasedOnAltitude();
	}
	else if (this->keyToPressedStatusMap[godot::GlobalConstants::KEY_S] == true)
	{
		this->altitude -= this->descentRate;

		this->RegularAltitude();

		this->UpdateAltitudeLabel();

		this->UpdateShadowBasedOnAltitude();
	}

	this->set_position(
		this->get_position() + (godot::Vector2::UP * this->velocity * delta).rotated(
			this->aircraftSpritePtr->get_rotation()
		)
	);
}
