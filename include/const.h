#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <map>
#include <iterator>
#include <cstdlib>
#include <typeinfo>
#include <stdexcept>
#include <typeindex>

class GameObject;
using namespace std;
constexpr auto PlayerSpeed = 95.f;
const auto BPP = sf::VideoMode::getFullscreenModes()[0].bitsPerPixel;
const int SCREEN_W = 1430;
const int SCREEN_H = 800;
const int NUMBER_OF_TEXTURES = 12;
const int NUMBER_OF_BACKGROUNDS = 5;
const int NUMBER_OF_MENU_BUTTONS = 4;
const int NUMBER_OF_EFECTS = 3;
const int NUMBER_OF_MUSICS = 2;
const int NUMBER_OF_FONT = 1;
const int FIRST_LEVEL = 1;
const int DEFULT = 0;
const int AMOUNT_OF_GOBLETS = 2;
const int FPS = 60;
const int SIZE_OF_TEXT = 30;
const int NUMBER_OF_LEVELS = 2;
const int BUTTON_Y_LOCITION = 355;
const int MIDDLE_BUTTON_Y = 100;
const int BUTTON_Y = 40;
const int HEIGHT_OF_MAP = 10;
const int WIDTH_OF_MAP = 19;
const float OBJECTSIZE_X = 75.f;
const float OBJECTSIZE_Y = 75.f;
const float SPEED_ANI = 0.025;
const float SCREEN_X_SIZE = 1920.f;
const float SCREEN_Y_SIZE = 1050.f;
const std::string LEVEL_NAME = "resources/Board", FILE_EXTENSION = ".txt";
const std::string LEVEL = "LEVEL: ", TIME = "TIME: ", GOBLETS = "GOBLETS: ";
const sf::Vector2f MENU_BUTTON_SIZE = { 115.f, 90.f };
const sf::Vector2f SCALE_TO_THE_LEFT = { -1, 1 }, SCALE_TO_THE_RIGHT = { 1, 1 };


//---------------FontsType---------------

enum Fonts
{
	FONT_1,
};
//---------------ObjectType---------------

enum ObjectType
{
	PLAYER,
	WALL,
	DOOR,
	GOBLET,
	SQUARE_INSIDE_SQUARE,
	ENEMY,
	INFO_GOBLET,
	CLOCK,
	INFO_LEVEL,
	EMPTY_TILE,
	MUSIC_ON,
	MUSIC_OFF,
	MAX,
};
//---------------class Object---------------

enum class Object
{
	Door = 'D',
	Wall = '#',
	Player = 'P',
	Goblet = 'G',
	Enemy = 'E',
	EmptyTile = ' ',
};
//---------------Background----------------

enum Background
{
	MenuBackground,
	Level1Background,
	WinLevel,
	WonGame,
	HelpBackground,

};
//---------------Buttons----------------

enum Button
{
	Start,
	Help,
	Exit,
	Back,
};
//---------------MusicType----------------

enum MusicType
{
	MenuMusic,
	GameMusic,
};

//---------------SoundType----------------
enum SoundType
{
	DeathPlayerSound,
	ButtonClick,
	GobletEffect,
};


//----------------dirction---------------
const sf::Vector2f

		LEFT = sf::Vector2f((float)-1, 0),
		RIGHT = sf::Vector2f((float)1, 0),
		STAND = sf::Vector2f(0, 0),
		UP = sf::Vector2f(0, (float)(-1)),
		DOWN = sf::Vector2f(0, (float)(1));
