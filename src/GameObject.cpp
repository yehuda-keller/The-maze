#include "GameObject.h"


//------------constractor------------
GameObject::GameObject()
{
}
//---------------draw----------------
void GameObject::draw(sf::RenderWindow& window) {

	window.draw(m_sprite);
}
//-----------setPlayerPosition------------
void GameObject::setTilePosition(const sf::Vector2f pos) {
	m_sprite.setPosition(pos.x, pos.y);
}
//------------getSprite------------
const sf::Sprite& GameObject::getSprite() const {
	return m_sprite;
}
//---------------isExsposed--------------
void GameObject::setExposed()
{
	m_isExsposed = true;
}
//---------------isExisposed--------------
bool GameObject::isExposed() const
{
	return m_isExsposed;
}
//-----------setColor--------------
void GameObject::setColor(const sf::Color color) {

	m_sprite.setColor(color);
}
