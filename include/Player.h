#pragma once
#include "MovingOpject.h"
#include "const.h"
#include "Animation.h"
#include "GameResources.h"



class Player :	public MovingObject
{
public:
	Player						();
	virtual ~Player				() = default;
	void init					();
	void Move					(const sf::Vector2f& direction, const float& deltaTime);
	void updateAnimation		(const float&) {}//ignore
	virtual void draw			(sf::RenderWindow& window) override;
	void moveStepBack			();
	void incGoblet				();
	int getMountGoblet			();
	void setEnterDoor			(bool status);
	const bool getEnterDoor		() const;
	const bool getPlayerIsDead	() const;
	void setPlayerDeath	();

private:
	//--------------------private members--------------------

	Animation m_playerAnimation = Animation(GameResources::getGameResources().getObjectTexture(PLAYER)
		, sf::Vector2u(4, 4), 0.25);
	
	int m_goblet = 0;
	bool m_enterDoor = false;
	bool m_playerIsDead = false;

	sf::Text m_amountOfGoblets;
	sf::Sprite m_backgroundPlayer;
	sf::Vector2f m_lastDireation = DOWN;
	
	
	
};
