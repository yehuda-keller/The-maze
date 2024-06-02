#pragma once
#include "StaticObject.h"
#include "Const.h"
#include "Animation.h"


class EmptyTile : public StaticObject
{
public:
	EmptyTile				();
	~EmptyTile				() = default;
	void updateAnimation	(const int& a, const float& b) {};

private:

};
