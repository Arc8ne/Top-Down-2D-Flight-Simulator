#include "MainWorld.hpp"

#include "MainFollowCamera.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * godot_gdnative_init_options_ptr)
{
	godot::Godot::gdnative_init(godot_gdnative_init_options_ptr);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * godot_gdnative_terminate_options_ptr)
{
	godot::Godot::gdnative_terminate(godot_gdnative_terminate_options_ptr);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle)
{
	godot::Godot::nativescript_init(handle);

	godot::register_class<MainWorld>();

	godot::register_class<MainFollowCamera>();

	SimulatorCore::instancePtr = new SimulatorCore();
}
