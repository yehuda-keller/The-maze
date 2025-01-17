#include "GameResources.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include "const.h"
#include <cstdlib>
#include <stdexcept>



//----------------constractor----------------
GameResources::GameResources()
{

	m_background[MenuBackground].loadFromFile("resources/image/MenuBackground.png");
	m_background[Level1Background].loadFromFile("resources/image/Level1Background.png");
	m_background[WinLevel].loadFromFile("resources/image/WinLevel.png");
	m_background[WonGame].loadFromFile("resources/image/WonGame.png");
	m_background[HelpBackground].loadFromFile("resources/image/helpBackground.png");
	m_objectTexture[PLAYER].loadFromFile("resources/image/Player.png");
	m_objectTexture[ENEMY].loadFromFile("resources/image/Enemy.png");
	m_objectTexture[WALL].loadFromFile("resources/image/Wall.png");
	m_objectTexture[CLOCK].loadFromFile("resources/image/clock.png");
	m_objectTexture[EMPTY_TILE].loadFromFile("resources/image/Empty.png");
	m_objectTexture[DOOR].loadFromFile("resources/image/door.png");
	m_objectTexture[INFO_LEVEL].loadFromFile("resources/image/level.png");
	m_objectTexture[GOBLET].loadFromFile("resources/image/Goblet.png");
	m_objectTexture[INFO_GOBLET].loadFromFile("resources/image/InfoGoblet.png");
	m_objectTexture[SQUARE_INSIDE_SQUARE].loadFromFile("resources/image/SquareInsideSquare.png");
	m_objectTexture[MUSIC_ON].loadFromFile("resources/image/musicOn.png");
	m_objectTexture[MUSIC_OFF].loadFromFile("resources/image/musicOff.png");
	m_buttens[Start].loadFromFile("resources/image/startButton.png");
	m_buttens[Help].loadFromFile("resources/image/helpButton.png");
	m_buttens[Exit].loadFromFile("resources/image/exitButton.png");
	m_buttens[Back].loadFromFile("resources/image/BackButton.png");
	m_fontGame[FONT_1].loadFromFile("resources/font/TimeFont.ttf");
	m_music[MenuMusic].openFromFile("resources/music/menuMusic.ogg");
	m_music[GameMusic].openFromFile("resources/music/gameMusic.ogg");
	m_effects[DeathPlayerSound].loadFromFile("resources/sound/enemyDie.wav");
	m_effects[ButtonClick].loadFromFile("resources/sound/buttonClick.wav");
	m_effects[GobletEffect].loadFromFile("resources/sound/GobletEffect.wav");
	
}
//-------------BackgroundType---------------
sf::Texture& GameResources::getBackground(const Background type)
{
	switch (type)
	{
		// backgrounds
	case Background::MenuBackground:
		return m_background[MenuBackground];
	case Background::Level1Background:
		return m_background[Level1Background];
	case Background::WinLevel:
		return m_background[WinLevel];
	case Background::WonGame:
		return m_background[WonGame];
	case Background::HelpBackground:
		return m_background[HelpBackground];
	}
	throw std::runtime_error("No Texture of this type");
}


//-------------ButtonType---------------
sf::Texture& GameResources::getButton(const Button type)
{
	switch (type)
	{
		
	case Button::Start:
		return m_buttens[Start];
	case Button::Help:
		return m_buttens[Help];
	case Button::Exit:
		return m_buttens[Exit];
	case Button::Back:
		return m_buttens[Back];
	}
	throw std::runtime_error("No Texture of this type");
}



//-------------ButtonType---------------
sf::Texture& GameResources::getObjectTexture(const ObjectType type)
{
	switch (type)
	{

	case ObjectType::DOOR:
		return m_objectTexture[DOOR];
	case ObjectType::WALL:
		return m_objectTexture[WALL];
	case ObjectType::PLAYER:
		return m_objectTexture[PLAYER];
	case ObjectType::ENEMY:
		return m_objectTexture[ENEMY];
	case ObjectType::GOBLET:
		return m_objectTexture[GOBLET];
	case ObjectType::SQUARE_INSIDE_SQUARE:
		return m_objectTexture[SQUARE_INSIDE_SQUARE];
	case ObjectType::INFO_GOBLET:
		return m_objectTexture[INFO_GOBLET];
	case ObjectType::CLOCK:
		return m_objectTexture[CLOCK];
	case ObjectType::INFO_LEVEL:
		return m_objectTexture[INFO_LEVEL];
	case ObjectType::EMPTY_TILE:
		return m_objectTexture[EMPTY_TILE];
	case ObjectType::MUSIC_ON:
		return m_objectTexture[MUSIC_ON];
	case ObjectType::MUSIC_OFF:
		return m_objectTexture[MUSIC_OFF];
	}
	throw std::runtime_error("No Texture of this type");
}
//----------------getFont-----------------------
sf::Font& GameResources::getFont(const Fonts type) 
{
	switch (type)
	{
	
	case Fonts::FONT_1:
			return m_fontGame[FONT_1];
	}
	throw std::runtime_error("No Texture of this type");
	
}
//---------------PlayMusic----------------------
void GameResources::PlayMusic(const MusicType type)
{
	switch (type)
	{
	case MusicType::MenuMusic:
		m_music[GameMusic].stop();
		m_music[MenuMusic].play();
		m_music[MenuMusic].setVolume(50.f);
		m_music[MenuMusic].setLoop(true);
		return;
	case MusicType::GameMusic:
		m_music[MenuMusic].stop();
		m_music[GameMusic].play();
		m_music[GameMusic].setVolume(50.f);
		m_music[GameMusic].setLoop(true);
		return;
	}
	throw std::runtime_error("No Music of this type");
}
//---------------setMute--------------
void GameResources::setMute(bool status) {
	if (status) {
		m_music[MenuMusic].setVolume(0.0f);
		m_sound.setVolume(0.0f);
	}
	else {
		m_music[MenuMusic].setVolume(50.f);
		m_sound.setVolume(100.f);
	}
}
//-----------------playSound-------------
void GameResources::playSound(const SoundType type) {

	switch (type)
	{
	case SoundType::DeathPlayerSound:
		m_sound.setBuffer(m_effects[DeathPlayerSound]);
		m_sound.play();
		return;
	case SoundType::ButtonClick:
		m_sound.setBuffer(m_effects[ButtonClick]);
		m_sound.play();
		return;
	case SoundType::GobletEffect:
		m_sound.setBuffer(m_effects[GobletEffect]);
		m_sound.play();
		return;
	}
	throw std::runtime_error("No Sound of this type");



}
