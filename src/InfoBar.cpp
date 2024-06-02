
#include "InfoBar.h"

//-------------------constractor-------------
InfoBar::InfoBar()
{
	//set font
	m_levelText.setFont(GameResources::getGameResources().getFont(FONT_1));
	m_timeText.setFont(GameResources::getGameResources().getFont(FONT_1));
	m_GolbetText.setFont(GameResources::getGameResources().getFont(FONT_1));

	//set text size
	m_levelText.setCharacterSize(SIZE_OF_TEXT);
	m_timeText.setCharacterSize(SIZE_OF_TEXT);
	m_GolbetText.setCharacterSize(SIZE_OF_TEXT);

	//set text color
	m_levelText.setFillColor(sf::Color::White);
	m_timeText.setFillColor(sf::Color::White);
	m_GolbetText.setFillColor(sf::Color::White);

	m_gobeltltSprite.setTexture(GameResources::getGameResources().getObjectTexture(INFO_GOBLET));
	m_gobeltltSprite.setPosition(900, 760);


	m_clockSprite.setTexture(GameResources::getGameResources().getObjectTexture(CLOCK));
	m_clockSprite.setPosition(610, 760);

	m_levelSprite.setTexture(GameResources::getGameResources().getObjectTexture(INFO_LEVEL));
	m_levelSprite.setPosition(410, 760);
}
//-------------------distractor-------------
InfoBar::~InfoBar()
{

}
//-------------------setLevelNum-------------
void InfoBar::setLevelNum(const int num) {

	m_levelNum = num;
}
//-------------------getLevelNum-------------
const int InfoBar::getLevelNum() const {

	return m_levelNum;
}
//-------------drawInfoBarText---------------
void InfoBar::drawInfoBarText(sf::RenderWindow& window, const int time) {

	//draw level number
	m_levelText.setString(LEVEL + to_string(m_levelNum));
	m_levelText.setPosition(450,760);
	window.draw(m_levelText);

	//draw level time
	m_timeText.setPosition(650, 760);
	m_timeText.setString(TIME + to_string(time));
	window.draw(m_timeText);

	m_GolbetText.setPosition(950, 760);
	m_GolbetText.setString(GOBLETS);
	window.draw(m_GolbetText);

	window.draw(m_gobeltltSprite);
	window.draw(m_clockSprite);
	window.draw(m_levelSprite);
}