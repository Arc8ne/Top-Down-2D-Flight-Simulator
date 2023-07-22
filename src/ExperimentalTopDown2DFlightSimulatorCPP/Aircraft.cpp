#include "Aircraft.hpp"

Aircraft::Aircraft(godot::Sprite* aircraftSpritePtr)
{
    this->aircraftSpritePtr = aircraftSpritePtr;

    godot::Vector2 aircraftSpriteRectSize = this->aircraftSpritePtr->get_rect().size;

    this->area = aircraftSpriteRectSize.x * aircraftSpriteRectSize.y;
}

double Aircraft::GetLift()
{
    return (1.0 / 2.0) * this->airPressure * (this->velocity * this->velocity).length() * this->liftCoefficient * this->area;
}

double Aircraft::GetDrag()
{
    return (1.0 / 2.0) * this->airPressure * (this->velocity * this->velocity).length() * this->dragCoefficient * this->area;
}
