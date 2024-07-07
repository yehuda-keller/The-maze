#pragma once

#include "GameResources.h"
#include "const.h"
#include "Animation.h"


class GameObject
{
public:
	GameObject					();
	virtual ~GameObject			() = default;

	void setExposed				();
	bool isExposed				() const;
	virtual void draw			(sf::RenderWindow& window);
	void setTilePosition		(const sf::Vector2f pos);
	const sf::Sprite& getSprite	() const;
	void setColor				(const sf::Color color);
	


protected:
	//------------------protected members-----------------------

	bool			m_isExsposed = false;
	sf::Sprite		m_sprite;
}; 

