#pragma once
#include "GameObject.h"


class MovingObject : public GameObject {

public:
	using GameObject::GameObject;
	virtual ~MovingObject			() = default;
	virtual void Move				(const sf::Vector2f& direction, const float& deltaTime) = 0;
	virtual void moveStepBack		() = 0;
	virtual void updateAnimation	(const float& s) {};

private:
	
	
	
};