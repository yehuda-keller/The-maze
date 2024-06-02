#pragma once
#include "MovingOpject.h"
#include "const.h"
#include "Animation.h"


class Enemy : public MovingObject
{
public:
	Enemy						();
	virtual ~Enemy				() = default;

	virtual void Move			(const sf::Vector2f& direction, const float& deltaTime);
	void setDirection			();
	sf::Vector2f getDirection	() const;
	void moveStepBack			();
	void updateAnimation		(const float&) {}//ignore
	
	
private:

	//-------------------------private members-----------------------
	Animation				m_enemyAnimation = Animation(GameResources::getGameResources().getObjectTexture(PLAYER)
							, sf::Vector2u(4, 4), 0.25);
	sf::Vector2f			m_lastDireation = STAND;
	sf::Vector2f			m_direction = LEFT;
	


};
