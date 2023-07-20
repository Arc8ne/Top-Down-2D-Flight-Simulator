#include "MainWorld.hpp"

#include "MainFollowCamera.hpp"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * godot_gdnative_init_options_ptr)
{
	Godot::gdnative_init(godot_gdnative_init_options_ptr);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * godot_gdnative_terminate_options_ptr)
{
	Godot::gdnative_terminate(godot_gdnative_terminate_options_ptr);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle)
{
	Godot::nativescript_init(handle);

	register_class<MainWorld>();

	register_class<MainFollowCamera>();
}
