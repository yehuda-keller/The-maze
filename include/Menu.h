#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include "const.h"
#include "GameResources.h"

class Menu
{
public:
	Menu			();
	~Menu			();
	void runMenu	(sf::RenderWindow&);
	

private:
	//----------------private functions------------------

	void handleClick		(bool&, sf::RenderWindow&);
	void handleMouseMove	(const sf::RenderWindow&);
	void drawMenu			(sf::RenderWindow&);
	void helpButton			(sf::RenderWindow& window);
	void drawHelpButton		(sf::RenderWindow& window);

	//-------------------private members-----------------

	std::vector<sf::RectangleShape> m_button;
	sf::Sprite						m_soundStatus;
	bool							m_drawSoundStatus = false;
	bool							m_soundStat = true;
};
