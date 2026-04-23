#pragma once
#include "Entity.h"

class Resistor : public Entity
{
public:
	void OnCollision(Entity* other) override;
	float  HorizontalSpeed;
	float VerticalSpeed;
	int life = 3;
	int speed = 10;   
};

