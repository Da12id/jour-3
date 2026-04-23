#pragma once
#include "Entity.h"

class Speeder : public Entity
{
public:
	void OnCollision(Entity* other) override;
	float  HorizontalSpeed;
	float VerticalSpeed;
	int life = 3;
	int speed = 30;
};

