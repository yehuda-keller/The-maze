#include "Enemy.h"

//-------------------------constractor-------------------
Enemy::Enemy()
{
	m_sprite.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::ENEMY));
	m_sprite.setScale(0.9, 0.9);
	m_sprite.setTextureRect(*m_enemyAnimation.get_uvRect());
	

}

//--------------------------move------------------------
void Enemy::Move(const sf::Vector2f& direction, const float& deltaTime)
{
	
	m_lastDireation = sf::Vector2f(m_direction.x * PlayerSpeed * deltaTime, m_direction.y * PlayerSpeed * deltaTime);
	m_sprite.move(m_lastDireation);
	m_enemyAnimation.update(m_enemyAnimation.getRowOfStandatAni(m_direction), deltaTime);
	m_sprite.setTextureRect(*m_enemyAnimation.get_uvRect());
	
}
//--------------------------setDirection------------------
void Enemy::setDirection()
{
	int dir = rand() % 4;
	switch (dir)
	{
	case 0:
		m_direction = UP;
		break;
	case 1:
		m_direction = DOWN;
		break;
	case 2:
		m_direction = LEFT;
		break;
	case 3:
		m_direction = RIGHT;
		break;
	}
}
//-----------------------------moveStepBack-------------------
void Enemy::moveStepBack() {

	m_sprite.move(-m_lastDireation);
}


//---------------------------getDirection----------------------
sf::Vector2f Enemy::getDirection() const
{
	return  m_direction;
}
