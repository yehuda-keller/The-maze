#pragma once
#include <fstream>
#include "GameResources.h"
#include "MovingOpject.h"
#include "StaticObject.h"
#include "CollisionHandling.h"
#include "Wall.h"
#include "Door.h"
#include "Player.h"
#include "Goblet.h"
#include "Enemy.h"
#include "EmptyTile.h"
#include "Graph.h"


class Board
{
public:
	Board();
	~Board();
	void createBoard						(const int LevelNum);
	void drawObjects					(sf::RenderWindow& window) const;
	void moveObjects					(const float& elapsedTime);
	void setWinGame						(const bool win);
	void movePlayer						(const sf::Vector2f& direction, const float& deltaTime);
	void checkExsposedObject			();
	void checkWheterMakeDFS				();
	void paintTheTrackViaDFS			();
	void addEdgesForGraph				();
	void checkNeighborsAndInsert		(const int& row, const int& col);
	void getPositionOfSourceAndTarget	(int& source, int& target);
	bool getPlayerStatus				();
	const bool getWinLevel				() const;
	const bool getWinGame				() const;
	const int getTime					() const;
private:

	//---------------------private func------------------------
	void paintTheTrack(const vector<int>& track);


	void collisions					();
	void initObjects				();
	void readFile					(ifstream&);
	void createObject				(const Object type, const sf::Vector2f location
									,vector<unique_ptr<StaticObject>>& Stemp
									,vector<unique_ptr<MovingObject>>& Mtemp);
	const sf::Vector2f findLocation (const int row, const int col) const;
	void updateAnimations			(const int& a, const float& b);

	//-------------------private members------------------------

	unique_ptr<Player>						 m_player;
	vector<vector<unique_ptr<StaticObject>>> m_staticObjects;
	vector<vector<unique_ptr<MovingObject>>> m_movingObjects;
	Graph m_graph = Graph(WIDTH_OF_MAP * HEIGHT_OF_MAP);


	int									m_row =			DEFULT;
	int									m_col =			DEFULT;
	int									m_timeLevel =	DEFULT;
	bool								m_winLevel =	false;
	bool								m_winGame =		false;
	bool								m_DFS =			false;
};	
