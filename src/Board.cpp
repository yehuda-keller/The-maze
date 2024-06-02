
#include "Board.h"
#include <sstream>
#include "const.h"
#include "GameResources.h"
#include "GameObject.h"


//----------------------------------constractor------------------------------
Board::Board()
{

}
//-----------------------------------distractor-----------------------------
Board::~Board()
{

}
//------------------------------------setBoard-------------------------------
void Board::createBoard(const int levelNum) {

	// Initialize the game objects and clear previous board data
	initObjects();

	// Construct the level file name based on the level number
	std::string levelName = LEVEL_NAME;
	levelName += std::to_string(levelNum);
	levelName += FILE_EXTENSION;

													// Open the level file
	ifstream file = std::ifstream(levelName);
	if (file)
		readFile(file);								// Read the level data from the file
	else
		m_winGame = true;							// no more levels to read

	m_winLevel = false;								// Reset win level flag for the next level/game
}
//-----------------------------------readFile---------------------------
//Reads the level file and creates objects on the game board based on the file contents.
void Board::readFile(std::ifstream& fileText) {


	// Read the board size and time limit from the level file
	auto lineInText = std::string();		

	try {
		if (!getline(fileText, lineInText)) {
			throw runtime_error("Can't read from file");
		}

		auto readBoardSize = istringstream(lineInText);
		readBoardSize >> m_row >> m_col >> m_timeLevel;
		m_DFS = false;
		

		// read the  file and create the objects
		for (int row = 0; row < m_row; row++) {
			if (!getline(fileText, lineInText)) {
				throw runtime_error("Can't read the line from file");
			}

			vector<unique_ptr<StaticObject>> Stemp;
			vector<unique_ptr<MovingObject>> Mtemp;

			for (int col = 0; col < lineInText.size(); col++) {

				createObject(Object(lineInText[col]), findLocation(row, col), Stemp, Mtemp);
			}
			m_staticObjects.push_back(move(Stemp));
			m_movingObjects.push_back(move(Mtemp));
		}
		
	}
	catch (std::runtime_error& exception) {
		std::cerr << "Exception: " << exception.what() << '\n';
		exit(EXIT_FAILURE);
	}

	// Add edges for the graph used in DFS
	addEdgesForGraph();
}
//---------------------------------findLocation----------------------------
const sf::Vector2f Board::findLocation(const int row, const int col) const {

	// Calculate the position of an object based on row and column
	sf::Vector2f location;
	location.x = OBJECTSIZE_X * col;
	location.y = OBJECTSIZE_Y * row;
	return location;
}

//-------------------------------------createObject--------------------------------
void Board::createObject(const Object type, const sf::Vector2f		location,
							   vector<unique_ptr<StaticObject>>&	Stemp	,
							   vector<unique_ptr<MovingObject>>&	Mtemp) 
{

	// Create and initialize objects based on the provided type
	switch (type) {

	case Object::Player:
		m_player = std::make_unique<Player>();
		m_player->setTilePosition(location);
		Stemp.emplace_back(std::make_unique<EmptyTile>());
		Stemp[Stemp.size() - 1]->setTilePosition(location);
		break;
	case Object::Enemy:
		Mtemp.emplace_back(std::make_unique<Enemy>());
		Mtemp[Mtemp.size() - 1]->setTilePosition(location);
		Stemp.emplace_back(std::make_unique<EmptyTile>());
		Stemp[Stemp.size() - 1]->setTilePosition(location);
		break;
	case Object::Wall:
		Stemp.emplace_back(std::make_unique<Wall>());
		Stemp[Stemp.size() - 1]->setTilePosition(location);
		break;
	case Object::Door:
		Stemp.emplace_back(std::make_unique<Door>());
		Stemp[Stemp.size() - 1]->setTilePosition(location);
		break;
	case Object::Goblet:
		Stemp.emplace_back(std::make_unique<Goblet>());
		Stemp[Stemp.size() - 1]->setTilePosition(location);
		break;
	case Object::EmptyTile:
		Stemp.emplace_back(std::make_unique<EmptyTile>());
		Stemp[Stemp.size() - 1]->setTilePosition(location);
		break;
	}


}
//----------------------------initObjects------------------------------
void Board::initObjects() {

	// Clear the board data and initialize game objects
	m_staticObjects.clear();
	m_movingObjects.clear();
	m_graph.clearEdge();
	m_graph.resetGraph();
	m_DFS = false;

}
//-------------------------------drawObjects----------------------------
void Board::drawObjects(sf::RenderWindow& window) const {

	// Draw static objects
	for (size_t i = 0; i < m_staticObjects.size(); i++)
		for (size_t j = 0; j < m_staticObjects[i].size(); j++)
			m_staticObjects[i][j]->draw(window);

	// Draw moving objects
	for (size_t i = 0; i < m_movingObjects.size(); i++)
		for (size_t j = 0; j < m_movingObjects[i].size(); j++)
			m_movingObjects[i][j]->draw(window);

	// Draw the player
	m_player->draw(window);


}

//-------------------------------getWinGame-----------------------------
const bool Board::getWinGame() const {

	return m_winGame;
}
//-----------------------------setWinGame------------------------------
void Board::setWinGame(const bool win) {

	m_winGame = win;
}
//------------------------------getWinLevel-----------------------------
const bool Board::getWinLevel() const {

	return  m_player->getEnterDoor();
}
//------------------------------getTime---------------------------------
const int Board::getTime() const {

	return m_timeLevel;
}
//-------------------------------movePlayer-----------------------------
void Board::movePlayer(const sf::Vector2f& direction, const float& elapsedTime)
{
	// Move the player based on the provided direction key
	m_player->Move(direction, elapsedTime);


	// check collisions
	collisions();


	//exposed objects if needed
	checkExsposedObject();

}

//-------------------------------------collide-----------------------------
bool collide(GameObject& a, GameObject& b)
{
	return a.getSprite().getGlobalBounds().intersects(b.getSprite().getGlobalBounds());
}
//------------------------------------collisions---------------------------
void Board::collisions() {



	// Collide player with static objects
	for (const auto& row : m_staticObjects) {
		for (const auto& staticObject : row) {
			if (collide(*m_player, *staticObject))
				processCollision(*m_player, *staticObject);
		}
	}

	// Collide player with moving objects
	for (const auto& row : m_movingObjects) {
		for (const auto& movingObject : row) {
			if (collide(*m_player, *movingObject))
				processCollision(*m_player, *movingObject);
		}
	}

	// Collide moving objects with static objects
	for (const auto& row : m_movingObjects) {
		for (const auto& movingObject : row) {
			if (typeid(*movingObject) == typeid(Enemy)) {
				Enemy& enemy = dynamic_cast<Enemy&>(*movingObject);
				// Process Enemy-specific collision logic if needed
			}

			for (const auto& staticRow : m_staticObjects) {
				for (const auto& staticObject : staticRow) {
					if (collide(*movingObject, *staticObject))
						processCollision(*movingObject, *staticObject);
				}
			}
		}
	}
	//  make DFS if needed
	checkWheterMakeDFS();
}
//-----------------------------------checkExsposedObject------------------------
/**
 * Checks if any objects on the board are exposed and performs actions if needed.
 * If an object is exposed, it replaces the object with an empty tile at the same position.
 */
void Board::checkExsposedObject() {

	// Check if any objects are exposed and perform actions if needed
	for (size_t i = 0; i < m_staticObjects.size(); i++)
		for (size_t j = 0; j < m_staticObjects[i].size(); j++)
			if (m_staticObjects[i][j]->isExposed()) {

				// Retrieve the position of the exposed object
				auto pos = m_staticObjects[i][j]->getSprite().getPosition();

				// Release the memory of the exposed object and create an empty tile in its place
				m_staticObjects[i][j].release();
				m_staticObjects[i][j] = std::make_unique<EmptyTile>();
				m_staticObjects[i][j]->setTilePosition(pos);
			}
}
//--------------------------moveObjects------------------------------
//Moves the moving objects on the game board in a specific direction.
void Board::moveObjects(const float& elapsedTime) {

	const sf::Vector2f& direction = LEFT;// Set the movement direction (change it as needed)

	for (auto& row : m_movingObjects) {
		for (auto& movable : row) {
			movable->Move(direction, elapsedTime);   // Move the movable object in the specified direction
			collisions();							 // Check for collisions with other objects
		}
	}

	updateAnimations(DEFULT, SPEED_ANI);			 // Update the animations of the objects (change it as needed)
}
//-----------------------------updateAnimation--------------------------
void Board::updateAnimations(const int& imagCount, const float& speed) {

	for (auto& row : m_staticObjects) {
		for (auto& staticObject : row) {
			staticObject->updateAnimation(imagCount, speed);
		}
	}
}
//--------------------------checkWheterMakeDFS------------------------
void Board::checkWheterMakeDFS() {

	// Check conditions and make DFS if needed
	if (m_player->getMountGoblet() == AMOUNT_OF_GOBLETS && !m_DFS)
		paintTheTrackViaDFS();
}

//-------------------------------paintTheTrackViaDFS----------------------
/**
 * Paints the track on the game board using the Depth-First Search (DFS) algorithm.
 * The track represents the path from the source to the target.
 */
void Board::paintTheTrackViaDFS() {

	// Paints the track on the board using Depth-First Search (DFS) algorithm.
	int source, target;
	bool found = false;
	vector<int> track;
	m_graph.resetGraph(); // Reset the graph used in DFS

	m_DFS = true;		// Enable DFS mode

	getPositionOfSourceAndTarget(source, target); // Get the positions of the source and target
	m_graph.DFS(source, target, found);			  // Perform DFS to find the track
	track = m_graph.getTrack();					  // Get the track from the graph

	paintTheTrack(track);						  // Paint the track on the game board
}
//-------------------------addEdgesForGraph---------------------------
/**
 * Adds edges to the graph for the game board based on the static objects.
 * Edges are added between adjacent non-wall objects.
 */
void Board::addEdgesForGraph() {

	// Adds edges to the graph for the board based on the static objects.
	for (size_t row = 0; row < m_staticObjects.size(); row++) {
		for (size_t col = 0; col < m_staticObjects[row].size(); col++)
			if (typeid(*m_staticObjects[row][col]) != typeid(Wall))
				checkNeighborsAndInsert(row, col);// Check neighbors and insert edges
	}
}
//--------------------checkNeighborsAndInsert--------------------------
void Board::checkNeighborsAndInsert(const int& row, const int& col) {

	// Checks the neighbors of the specified tile and inserts edges into the graph.
	int currentNode = col + row * WIDTH_OF_MAP;
	//top node
	if (row - 1 > -1 && typeid(*m_staticObjects[row - 1][col]) != typeid(Wall))
		m_graph.addEdge(currentNode, (row - 1) * WIDTH_OF_MAP + col);
	//bottom node
	if (row + 1 < HEIGHT_OF_MAP && typeid(*m_staticObjects[row + 1][col]) != typeid(Wall))
		m_graph.addEdge(currentNode, (row + 1) * WIDTH_OF_MAP + col);

	// left node
	if (col - 1 > -1 && typeid(*m_staticObjects[row][col - 1]) != typeid(Wall))
		m_graph.addEdge(currentNode, row * WIDTH_OF_MAP + col - 1);
	// right node
	if (col + 1 < WIDTH_OF_MAP && typeid(*m_staticObjects[row][col + 1]) != typeid(Wall))
		m_graph.addEdge(currentNode, row * WIDTH_OF_MAP + col + 1);
}
//---------------------------getPositionOfSourceAndTarget-------------------
/**
 * Determines the position of the source and target tiles for the Depth-First Search (DFS) algorithm.
 * The source position is set to the player's current position, and the target position is set to the door's position.
 * source The position of the source tile (output parameter).
 * target The position of the target tile (output parameter).
 */
void Board::getPositionOfSourceAndTarget(int& source, int& target) {

	// Determines the position of the source and target tiles for DFS.
	for (int row = 0; row < m_staticObjects.size(); row++)
		for (int col = 0; col < m_staticObjects[row].size(); col++) {

			if (collide(*m_player, *m_staticObjects[row][col]) && typeid(*m_staticObjects[row][col]) != typeid(Wall)) {
				// Set the source position based on the player's current tile
				source = row * WIDTH_OF_MAP + col;
			}
				
			if (typeid(*m_staticObjects[row][col]) == typeid(Door)) {
				// Set the target position based on the door tile
				target = row * WIDTH_OF_MAP + col;
			}
				
		}

}
//------------------------------------paintTheTrack----------------------------
void Board::paintTheTrack(const vector<int>& track) {

	// Paints the track on the board based on the given track vector.
	for (const auto i : track)
		m_staticObjects[i / WIDTH_OF_MAP][i % WIDTH_OF_MAP]->setColor(sf::Color::Black);

	
}
//------------------------------------getPlayerStatus-----------------------------
/**
 * Retrieves the status of the player.
 * @return A boolean value indicating whether the player is dead (true) or alive (false).
 */
bool Board::getPlayerStatus()
{
	return m_player->getPlayerIsDead();
}