#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Board.h"
#include "InfoBar.h"
#include "Player.h"




class GameController
{
public:
	GameController					();
	~GameController					();
	sf::Vector2f getPlayerDirection	();
	void handleEvents				();
	void draw						();
	void execute						();
	void resetLevelTime				();
	void handleLevelTime			();
	void runGame					();
	void runLevel					();
	void printLevelWon				();
	void printGameWon				();

private:
	
	//--------------------private members-------------------------

	Menu					m_menu;
	Board					m_board;
	InfoBar					m_infoBar;

	sf::RenderWindow		m_window;
	sf::Time				m_gameTime;							
	sf::Clock				m_deltaTime,					   
							m_timeOfCurrLevel;					
	bool					m_endOfTime = false;				
};
