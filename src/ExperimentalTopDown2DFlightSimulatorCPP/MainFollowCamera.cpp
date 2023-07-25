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

void MainFollowCamera::RegulateAltitude()
{
	if (this->altitude < 0)
	{
		this->altitude = 0;
	}
}

void MainFollowCamera::UpdateAirspeedLabel()
{
	this->airspeedLabelPtr->set_text(
		godot::String::num(this->velocity) + (godot::String)" kts"
	);

	// godot::Godot::print("Lift: " + this->GetLift());
}

void MainFollowCamera::UpdateAltitudeLabel()
{
	this->altitudeLabelPtr->set_text(
		godot::String::num(this->altitude) + (godot::String)" ft"
	);

	if (this->altitude < this->lowAltitude)
	{
		this->altitudeLabelPtr->add_color_override(
			"font_color",
			this->redColor
		);
	}
	else
	{
		this->altitudeLabelPtr->add_color_override(
			"font_color",
			this->whiteColor
		);
	}
}

void MainFollowCamera::UpdateShadowBasedOnAltitude()
{
	this->shadowOffset.x = this->altitude * -0.2;

	this->shadowOffset.y = this->altitude * 0.2;

	this->aircraftShadowPtr->set_position(
		this->aircraftSpritePtr->get_position() + this->shadowOffset
	);
}

void MainFollowCamera::UpdateShadowBasedOnRotation()
{
	this->aircraftShadowPtr->set_rotation(
		this->aircraftSpritePtr->get_rotation()
	);
}

void MainFollowCamera::UpdateHUDBasedOnCameraZoom()
{
	// return;

	this->hudVBoxContainerPtr->set_position(
		this->get_viewport_rect().size / 2 + godot::Vector2(40, 40)
	);
}

godot::Vector2 MainFollowCamera::GetLift()
{
	godot::Vector2 lift = godot::Vector2(0, 0);

	lift = (1.0 / 2.0) * 1.0 * (this->velocity * this->velocity) * 1.0 * this->aircraftSpritePtr->get_rect().get_size();

	return lift;
}

void MainFollowCamera::OnInputMouseMotion(godot::InputEventMouseMotion* inputEventMouseMotionPtr)
{

}

void MainFollowCamera::OnInputMouseButton(godot::InputEventMouseButton* inputEventMouseButtonPtr)
{
	if (inputEventMouseButtonPtr->is_pressed() == true)
	{
		int64_t buttonIndex = inputEventMouseButtonPtr->get_button_index();

		if (buttonIndex == godot::GlobalConstants::BUTTON_WHEEL_UP)
		{
			this->set_zoom(
				this->get_zoom() - godot::Vector2(0.1, 0.1)
			);
		}
		else if (buttonIndex == godot::GlobalConstants::BUTTON_WHEEL_DOWN)
		{
			this->set_zoom(
				this->get_zoom() + godot::Vector2(0.1, 0.1)
			);
		}
	}
}

void MainFollowCamera::OnGPSCheckButtonToggled(bool isButtonPressed)
{

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
	SimulatorCore::instancePtr->GenerateWorld(
		godot::Object::cast_to<godot::Node2D>(
			this->get_node("/root/MainWorld")
		)
	);

	this->aircraftSpritePtr = godot::Object::cast_to<godot::Sprite>(
		this->get_node("AircraftSprite")
	);

	this->aircraftShadowPtr = godot::Object::cast_to<godot::Sprite>(
		this->get_node("AircraftShadowSprite")
	);

	this->hudVBoxContainerPtr = godot::Object::cast_to<godot::VBoxContainer>(
		this->get_node("HUDCanvasLayer/HUDVBoxContainer")
	);

	this->airspeedLabelPtr = godot::Object::cast_to<godot::Label>(
		this->hudVBoxContainerPtr->get_node("AirspeedLabel")
	);

	this->altitudeLabelPtr = godot::Object::cast_to<godot::Label>(
		this->hudVBoxContainerPtr->get_node("AltitudeLabel")
	);

	this->gpsCheckButtonPtr = godot::Object::cast_to<godot::CheckButton>(
		this->get_node(
			"HUDCanvasLayer/TopRightVBoxContainer/GPSCheckButton"
		)
	);

	this->gpsCheckButtonPtr->connect(
		"toggled",
		this,
		"OnGPSCheckButtonToggled"
	);

	this->UpdateAirspeedLabel();

	this->UpdateAltitudeLabel();

	this->UpdateHUDBasedOnCameraZoom();
}

void MainFollowCamera::_input(godot::InputEvent* inputEventPtr)
{
	if (inputEventPtr->is_class("InputEventKey") == true)
	{
		godot::InputEventKey* inputEventKeyPtr = godot::Object::cast_to<godot::InputEventKey>(inputEventPtr);
	
		this->keyToPressedStatusMap[inputEventKeyPtr->get_scancode()] = inputEventPtr->is_pressed();
	}
	else if (inputEventPtr->is_class("InputEventMouseButton") == true)
	{
		this->OnInputMouseButton(
			godot::Object::cast_to<godot::InputEventMouseButton>(
				inputEventPtr
			)
		);
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
		this->altitude += 1;

		this->RegulateAltitude();

		this->UpdateAltitudeLabel();

		this->UpdateShadowBasedOnAltitude();
	}
	else if (this->keyToPressedStatusMap[godot::GlobalConstants::KEY_S] == true)
	{
		this->altitude -= 1;

		this->RegulateAltitude();

		this->UpdateAltitudeLabel();

		this->UpdateShadowBasedOnAltitude();
	}

	this->set_position(
		this->get_position() + (godot::Vector2::UP * this->velocity * delta).rotated(
			this->aircraftSpritePtr->get_rotation()
		)
	);
}
