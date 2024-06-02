#include "GameController.h"
#include "GameResources.h"
#include "Player.h"
#include "const.h"

//----------------------------constractor---------------------------
GameController::GameController()
	:m_window(sf::VideoMode(SCREEN_W, SCREEN_H, BPP), "THE MAZE", sf::Style::Default)
{
	m_window.setFramerateLimit(FPS);
}
//-------------------------------disstractor------------------------
GameController::~GameController()
{
}
//---------------------------------execute---------------------------
//Executes the main game loop, including the menu, board creation, and running the game.
void GameController::execute()
{
	// Continue executing the game loop until the game window is closed
	while (m_window.isOpen()) {

		m_menu.runMenu(m_window);							// Run the game menu
		m_board.createBoard(m_infoBar.getLevelNum());		// Create the game board for the current level
		runGame();											// Run the main game loop

		// Display the game won message after completing all levels
		printGameWon();
		
	}
}
//----------------------------runGame-------------------------------
//Runs the main game loop, which includes multiple levels of the game.
void GameController::runGame()
{
	
	GameResources::getGameResources().PlayMusic(GameMusic);

	// Continue running the game until the win condition of the entire game is met
	while (!m_board.getWinGame())
	{
		resetLevelTime();
		runLevel();

		// Check if the level time has not ended
		if (!m_endOfTime) {	

			// Set the next level and display the level won message
			m_infoBar.setLevelNum(m_infoBar.getLevelNum() + 1);
			printLevelWon();
			
		}
		m_board.createBoard(m_infoBar.getLevelNum());

	}
	// Reset the level and game state for a new game
	m_board.createBoard(m_infoBar.getLevelNum());
	m_infoBar.setLevelNum(FIRST_LEVEL);
	m_board.setWinGame(false);
}
//---------------------------runLevel--------------------------------
//Runs the main loop for a single level of the game.
void GameController::runLevel()
{
	auto delta = m_deltaTime.restart();
	float elapsTime;
	m_window.setKeyRepeatEnabled(false);
	sf::Vector2f direction;

	// Continue running the level until the win condition is met or the player is dead
	while (!m_board.getWinLevel() )
	{
		draw();
		handleLevelTime();

		// Check if the level time has ended or the player is dead
		if (m_gameTime.asSeconds() < 0 || m_board.getPlayerStatus()) {	
			m_endOfTime = true;
			break;
		}
		handleEvents();
		elapsTime = m_deltaTime.restart().asSeconds();
		direction = getPlayerDirection();

		// Move the player and objects based on the player's direction and elapsed time
		if (STAND != direction)
			m_board.movePlayer(direction, elapsTime);
		m_board.moveObjects(elapsTime);
	}

}
//-------------------------------handleEvents-----------------------------
void GameController::handleEvents() {


	

	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			exit(EXIT_SUCCESS);
		case sf::Event::MouseMoved:
			break;
		case sf::Event::MouseButtonReleased:
			auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			break;
		}
		
		
	}
}
//-------------------------------draw-----------------------------
void GameController::draw() {

	m_window.clear();
	auto sprite = sf::Sprite(GameResources::getGameResources().getBackground(Background::Level1Background));
	m_window.draw(sprite);
	m_board.drawObjects(m_window);

	if (m_board.getTime() == 0)
		m_infoBar.drawInfoBarText(m_window, int(m_timeOfCurrLevel.getElapsedTime().asSeconds()));
	else
		m_infoBar.drawInfoBarText(m_window, int(m_gameTime.asSeconds()));

	m_window.display();
}

//------------------------updatePlayerDir---------------------------
sf::Vector2f GameController::getPlayerDirection() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return LEFT;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		return RIGHT;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		return UP;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return DOWN;

	return STAND;
}
//----------------------------resetTimeLevel--------------------------
void GameController::resetLevelTime() {

	m_timeOfCurrLevel.restart();
	m_gameTime = sf::seconds(float(m_board.getTime()));
	m_endOfTime = false;
}
//--------------------------------handleGameTime---------------------
void GameController::handleLevelTime() {

	if (m_board.getTime() > 0) {
		m_gameTime -= m_timeOfCurrLevel.getElapsedTime();
		m_timeOfCurrLevel.restart();
	}
}
//-----------------------------------printWinLevel-----------------------
void GameController::printLevelWon()
{

	if (m_infoBar.getLevelNum() > NUMBER_OF_LEVELS)
		return;
	m_window.clear();
	sf::Sprite winSprite(GameResources::getGameResources().getBackground(WinLevel));
	m_window.draw(winSprite);
	m_window.display();
	while (true)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			break;

}
//--------------------------------printWinGame---------------------
void GameController::printGameWon()
{

	m_window.clear();
	sf::Sprite winSprite(GameResources::getGameResources().getBackground(WonGame));
	m_window.draw(winSprite);
	m_window.display();
	while (true) 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			break;
}