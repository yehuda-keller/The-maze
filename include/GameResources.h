#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <vector>
#include "const.h"
#include <iostream>
#include <fstream>



class GameResources
{
public:
	static GameResources& getGameResources() {
		static auto resources = GameResources();
		return resources;
	}
	GameResources					(const GameResources&) = delete;
	void operator=					(const GameResources&) = delete;

	sf::Texture& getBackground		(const Background);
	sf::Texture& getButton			(const Button);
	sf::Texture& getObjectTexture	(const ObjectType);
	sf::Font& getFont				(const Fonts);
	void PlayMusic					(const MusicType);
	void playSound					(const SoundType type);
	void setMute					(bool status);

	

private:
	//-----------------------private func-------------------------

	GameResources					();


	//-----------------------private members----------------------

	sf::Texture			m_background[NUMBER_OF_BACKGROUNDS];
	sf::Texture			m_objectTexture[NUMBER_OF_TEXTURES];
	sf::Texture			m_buttens[NUMBER_OF_MENU_BUTTONS];
	sf::Font			m_fontGame[NUMBER_OF_FONT];
	sf::Music			m_music[NUMBER_OF_MUSICS];
	sf::SoundBuffer		m_effects[NUMBER_OF_EFECTS];
	sf::Sound			m_sound;
};

