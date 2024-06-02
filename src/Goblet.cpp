#include "Goblet.h"


//------------------------constractor--------------------------
Goblet::Goblet()
{
	m_sprite.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::GOBLET));
	m_sprite.setScale(0.3, 0.3);
	m_sprite.setTextureRect(*m_gobletAnimation.get_uvRect());
}
//---------------------updateAnimation--------------------------
void Goblet::updateAnimation(const int& a, const float& b)
{
    m_gobletAnimation.update(a, b);
    m_sprite.setTextureRect(*m_gobletAnimation.get_uvRect());
};