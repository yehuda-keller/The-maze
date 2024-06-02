#include "Door.h"


//----------------------constractor----------------------
Door::Door()
{
	m_sprite.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::DOOR));
	m_sprite.setScale(0.3, 0.3);
	m_sprite.setTextureRect(*m_doorAnimation.get_uvRect());
}
//------------------updateAnimation---------------------
void Door::updateAnimation(const int& a, const float& b) {
	m_doorAnimation.update(a, b);
	m_sprite.setTextureRect(*m_doorAnimation.get_uvRect());
};