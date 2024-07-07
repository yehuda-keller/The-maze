#include "EmptyTile.h"


//-------------------------constractor-------------------
EmptyTile::EmptyTile()
{
	m_sprite.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::EMPTY_TILE));
}
