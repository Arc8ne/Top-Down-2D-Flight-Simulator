#pragma once

#include <Godot.hpp>

#include <Node2D.hpp>

class MainWorld : public godot::Node2D
{
	GODOT_CLASS(MainWorld, godot::Node2D)
private:

public:
	static void _register_methods();

	void _init();

	void _ready();
};
