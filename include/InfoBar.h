#pragma once
#include "GameResources.h"

class InfoBar
{
public:
	InfoBar					();
	~InfoBar				();
	const int getLevelNum	() const;
	void setLevelNum		(const int num);
	void drawInfoBarText	(sf::RenderWindow&, const int time);

private:

	//------------------------private members--------------------

	sf::Sprite			m_gobeltltSprite;
	sf::Sprite			m_clockSprite;
	sf::Sprite			m_levelSprite;
	sf::Text			m_levelText;		
	sf::Text			m_timeText;		
	sf::Text			m_GolbetText;	    

	int					m_levelNum = 1;
};

