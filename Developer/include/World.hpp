//World.hpp
#ifndef _World_hpp_included_
#define _World_hpp_included_

#include <GameObject.hpp>
#include <SFML/Graphics.hpp>
#include <DataTypes.hpp>
#include <State.hpp>

#include <vector>

//============World======================
//
class World : public State {
public:

									World(sf::Font& font, int fontCharacterSize, int tileSize, std::string fileName);

	virtual void					update(float deltaTime, sf::RenderWindow& window, sf::View& view, config& config);
	virtual void					render(sf::RenderWindow& window, sf::View& view, config& config);

	void							resolveMapCollision(GameObject*, int, int);
	void							resolveObjectCollision(GameObject*, int);
	void							loadLevelMap(std::string);
	void							deleteLevelMap();

	//void							spawnObject(std::string);

private:

	sf::Clock						mSpawnClock;

	std::vector<std::vector<bool>>	mCollisionMap;

	sf::RectangleShape				mTile;

	//sf::Font						mFont;

	sf::Text						mTextHealth;
	sf::Text						mTextMana;
	sf::Text						mTextEnemyCount;
	sf::Text						mTextPlayerCoordinates;
	sf::Text						mTextMouseCoordinates;

};
//
//==========================================


#endif