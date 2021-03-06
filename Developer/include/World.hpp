//World.hpp
#ifndef _World_hpp_included_
#define _World_hpp_included_

#include <_includes_system.hpp>
#include <_includes_badass.hpp>


extern TextureHolder		gTextureHolder;

//============WORLD=========================
class World : public State {
public:

									World(std::string fileName, config& config, StateMachine* game);

	virtual void					initializeScripts();

	void							loadObjects();
	void							loadFactionKarmaMap(std::string filename);

	void							onCreate();
	void							onExit();

	//============UPDATE========================
	virtual void					update(float deltaTime, sf::RenderWindow& window, sf::View& view, config& config);
	virtual void					updateObjects(float deltaTime, config& config);
	virtual void					updateView(sf::RenderWindow& window, sf::View& view, config& config);
	void							updateMouseCoordinates(sf::RenderWindow& window, config& config, sf::Vector2f viewPosition);
	virtual void					updateGrid(config& config);
	virtual void					updateHUD(sf::RenderWindow& window);

	//============INPUT=========================
	virtual void					handleInput(config& config);

	//============SCRIPTS=======================
	void							zoomIn();
	void							zoomOut();

	//============RENDER========================
	virtual void					render(sf::RenderWindow& window, sf::View& view, config& config);
	virtual void					renderMap(sf::RenderWindow& window, sf::View& view, config& config);
	virtual void					renderObjects(sf::RenderWindow& window, sf::View& view, config& config);
	virtual void					renderHUD(sf::RenderWindow& window, sf::View& view, config& config);

	//============OTHER=========================
	void							resolveMapCollision(GameObject*, int direction, int tileSize);	//Direction:	0 == horizontal
	void							resolveObjectCollision(GameObject*, int direction);				//				1 == vertical

	std::vector<sf::Vector2i>		getAdjacentTiles(sf::Vector2i tile);
	bool							wavePathFind(sf::Vector2i source, sf::Vector2i destination, std::vector<sf::Vector2i>& path);

	//void							loadHUDInfo();
	bool							loadLevelMap(std::string fileName);
	void							buildCollisionMap();
	void							deleteLevelMap();

	bool							loadObject(std::string objectID);

	void							spawnObject(std::string objectID, sf::Vector2i coordinates, config& config);
	bool							areEnemies(GameObject& object1, GameObject& object2);

	//============GET===========================
	std::vector<std::vector<int>>&	getLevelMap();
	int								getMapHeight();
	int								getMapWidth();
	std::vector<std::vector<bool>>&	getCollisionMap();

	float							getViewWidth();
	float							getViewHeight();
	sf::Vector2i					getMouseCoordinates();
	std::map<std::string, bool>&	getFactionKarmaMap();
	bool							isPlayerAlive();

	//============SET===========================
	void							setMapHeight(int height);
	void							setMapWidth(int width);
	void							setPlayerAlive(bool isAlive);

private:

	config							mConfig;

	bool							mTerminateGame;

	sf::Clock						mSpawnClock;

	sf::Vector2i					mMouseCoordinates;

	std::vector<std::vector<int>>	mLevelMap;
	std::vector<std::vector<bool>>	mCollisionMap;
	int								mMapHeight;
	int								mMapWidth;

	//===============OBJECTS=======================
	std::map<std::string, bool>		mAvailableObjects;

	std::map<std::string, bool>		mFactionKarmaMap;	//true/false depending on karma associated with the faction.
														//true == good, false == bad.

	//===============OBJECT DATA===================
	std::map<std::string, 
		objectInput>				mObjectInput;

	std::map<std::string, 
		objectPhysics>				mObjectPhysics;

	std::map<std::string, 
		objectGraphics>				mObjectGraphics;

	std::map<std::string, 
		objectCombat>				mObjectCombat;

	std::map<std::string, 
		objectSocial>				mObjectSocial;

	//===============SCREEN========================
	sf::RectangleShape				mTile;

	bool							mPathHighlight;
	sf::RectangleShape				mPathTile;

	bool							mGridActive;
	sf::RectangleShape				mVerticalLine;
	sf::RectangleShape				mHorizontalLine;

	sf::Vector2f					mViewPosition;
	sf::FloatRect					mScreenCenter;
	float							mViewWidth;
	float							mViewHeight;

	//===============HUD===========================
	sf::Text						mTextHealth;
	sf::Text						mTextMana;
	sf::Text						mTextEnemyCount;
	sf::Text						mTextObjectCoordinates;
	sf::Text						mTextMouseCoordinates;
	sf::Text						mOutConsole;

	bool							mIsPlayerAlive;
	myGameObjectIter				mCenterObject;	//!!!! To be used in future. I hope.
	int								mCenterObjectN;	//Index of an object which acts as a view center.

};

#endif
