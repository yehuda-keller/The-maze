#include "Wall.h"


//------------------constractor-------------------
Wall::Wall()
{
	m_sprite.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::WALL));
}
