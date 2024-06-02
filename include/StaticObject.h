#pragma once
#include "GameObject.h"
#include "Animation.h"

class StaticObject : public GameObject {

public:
	using GameObject::GameObject;
	~StaticObject					() = default;
	virtual void updateAnimation	(const int& a, const float& b) = 0;
protected:
	

};