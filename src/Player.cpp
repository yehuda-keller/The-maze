
#include "Player.h"
//---------------------------constractor----------------------
Player::Player()
{
	init();
}
//--------------------------------init-------------------------
void Player::init()
{
	m_sprite.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::PLAYER));
	m_sprite.setScale(0.9, 0.9);
	m_sprite.setTextureRect(*m_playerAnimation.get_uvRect());


	m_backgroundPlayer.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::SQUARE_INSIDE_SQUARE));
	m_backgroundPlayer.setOrigin(m_backgroundPlayer.getTexture()->getSize().x / 2,
				   				 m_backgroundPlayer.getTexture()->getSize().y / 2);



	m_amountOfGoblets.setFont(GameResources::getGameResources().getFont(FONT_1));
	m_amountOfGoblets.setPosition(980, 760);
	m_amountOfGoblets.setFillColor(sf::Color::Yellow);
}

//--------------------------------move---------------------------
void Player::Move(const sf::Vector2f& direction, const float& deltaTime)
{

	m_lastDireation = sf::Vector2f(direction.x * PlayerSpeed * deltaTime, direction.y * PlayerSpeed * deltaTime);
	m_sprite.move(m_lastDireation);
	m_playerAnimation.update(m_playerAnimation.getRowOfStandatAni(direction), deltaTime);
	m_sprite.setTextureRect(*m_playerAnimation.get_uvRect());
}

//-----------------------------------draw-----------------------------
void Player::draw(sf::RenderWindow& window) {

	m_backgroundPlayer.setPosition(m_sprite.getPosition().x + 50, m_sprite.getPosition().y + 30);
	window.draw(m_sprite);
	window.draw(m_backgroundPlayer);
	m_amountOfGoblets.setString(to_string(m_goblet));
	m_amountOfGoblets.setPosition(1055, 760);
	window.draw(m_amountOfGoblets);
	
}


//-----------------------------moveStepBack-----------------------------
void Player::moveStepBack() {

	m_sprite.move(-m_lastDireation);
}

//----------------------------------incGoblet-------------------------
void Player::incGoblet() {

	m_goblet++;

}
//-------------------------------getMountGoblet-----------------------
int Player::getMountGoblet()
{
	return m_goblet;
}
//--------------------------------getEnterDoor-------------------------
const bool Player::getEnterDoor() const
{
	return m_enterDoor;
}
//--------------------------------setEnterDoor-------------------------
void Player::setEnterDoor(bool status)
{
	m_enterDoor = status;
}

//---------------------------------handlePlayerDeath--------------------
void Player::setPlayerDeath()
{
	m_playerIsDead = true;
	
}
//---------------------------------getPlayerIsDead------------------------
const bool Player::getPlayerIsDead() const
{
	return m_playerIsDead;
}