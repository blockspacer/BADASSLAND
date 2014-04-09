//World.cpp
#include <World.hpp>

extern TextureHolder		gTextureHolder;
extern sf::Font				gFont;
extern int					gFontSize;

//============WORLD======================
//
World::World(int tileSize, std::string fileName, config& config) {

	mSpawnClock.restart();

	loadLevelMap(fileName);


	//===============FONT==========================
	gFont.loadFromFile("sansation.ttf");
	gFontSize = 30;


	//===============TEXTURES======================
	gTextureHolder.load(Textures::HP_Bar, "./textures/HPBar.png");
	gTextureHolder.load(Textures::Elf_Red, "./textures/red_elf_sprite_list.png");
	gTextureHolder.load(Textures::Elf_Green, "./textures/green_elf_sprite_list.png");
	gTextureHolder.load(Textures::Elf_Yellow, "./textures/yellow_elf_sprite_list.png");
	//gTextureHolder.load(Textures::TileSet, "./textures/testTileSet.png");
	//gTextureHolder.load(Textures::HP_Potion, "./textures/healthPotion.png");

	//sf::Sprite tile(tileSet);


	//===============SOUND=========================
	//sf::SoundBuffer emenyHitSoundBuffer;

	//emenyHitSoundBuffer.loadFromFile("sound1.ogg");

	//sf::Sound emenyHitSound(emenyHitSoundBuffer);


	//===============HUD HEALTH====================
	mTextHealth.setFont(gFont);
	mTextHealth.setString("");
	mTextHealth.setCharacterSize(gFontSize);
	mTextHealth.setStyle(sf::Text::Bold);
	mTextHealth.setColor(sf::Color::Red);
	mTextHealth.setPosition(0, 0);


	//===============HUD MANA======================
	mTextMana.setFont(gFont);
	mTextMana.setString("");
	mTextMana.setCharacterSize(gFontSize);
	mTextMana.setStyle(sf::Text::Bold);
	mTextMana.setColor(sf::Color::Blue);
	mTextMana.setPosition(0, gFontSize);


	//===============HUD ENEMY COUNT===============
	mTextEnemyCount.setFont(gFont);
	mTextEnemyCount.setString("");
	mTextEnemyCount.setCharacterSize(gFontSize);
	mTextEnemyCount.setStyle(sf::Text::Bold);
	mTextEnemyCount.setColor(sf::Color::Color(184, 138, 0));
	mTextEnemyCount.setPosition(0, gFontSize * 2);


	//===============HUD PLAYER COORDINATES========
	mTextPlayerCoordinates.setFont(gFont);
	mTextPlayerCoordinates.setString("");
	mTextPlayerCoordinates.setCharacterSize(gFontSize);
	mTextPlayerCoordinates.setStyle(sf::Text::Bold);
	mTextPlayerCoordinates.setColor(sf::Color::Color(125, 145, 176));
	mTextPlayerCoordinates.setPosition(0, gFontSize * 3);


	//===============HUD MOUSE COORDINATES=========
	mTextMouseCoordinates.setFont(gFont);
	mTextMouseCoordinates.setString("");
	mTextMouseCoordinates.setCharacterSize(gFontSize);
	mTextMouseCoordinates.setStyle(sf::Text::Bold);
	mTextMouseCoordinates.setColor(sf::Color::Color(125, 145, 176));
	mTextMouseCoordinates.setPosition(0, gFontSize * 6);


	//===============TILE OBJECT===================
	mTile = sf::RectangleShape(sf::Vector2f(tileSize, tileSize));



	//===============KEY BINDINGS==================
	sf::Keyboard::Key playerControls[4] = { sf::Keyboard::Key::Up,
											sf::Keyboard::Key::Down,
											sf::Keyboard::Key::Left,
											sf::Keyboard::Key::Right };

	sf::Keyboard::Key enemyControls[4] =  {	sf::Keyboard::Key::W,		//!!!Move to update.
											sf::Keyboard::Key::S,		//!!!Move controls to global or somewhere else.
											sf::Keyboard::Key::A,
											sf::Keyboard::Key::D };

	//Creating player.
	getGameObjects().push_back( *(new GameObject(	new KeyboardInputComponent(playerControls),
													new DynamicPhysicsComponent(sf::FloatRect(config.playerStartingX, config.playerStartingY, config.tileSize, config.tileSize), 0.1),
													new HumanoidGraphicsComponent(Textures::Elf_Green),
													new HumanoidCombatComponent(150, 150, 40, 40, 2),
													new HumanoidSocialComponent("Player 1", "yellow_elves")  )) );

}

void World::update(float deltaTime, sf::RenderWindow& window, sf::View& view, config& config) {
	
	//===============UPDATING GAME LOGIC===========
	for(int i = 0; i < getGameObjects().size(); ++i)	
		getGameObjects()[i].update(deltaTime, &config, *this);
	
	//Deleting objects marked for removal.
	for(int i = 0; i < getGameObjects().size(); ++i) {
		if(getGameObjects()[i].getCombat()->isMarkedForRemoval()) {

			getGameObjects().erase(getGameObjects().begin() + i);
			--i;
			getGameObjects()[i].getInput()->setTargeting(false);

		}
	}


	//===============SPAWNING OBJECTS==============
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::G)) && (mSpawnClock.getElapsedTime().asSeconds() > 0.25)) {	//!!!Replace with a global variable.
		getGameObjects().push_back( *(new GameObject(	new BotActiveInputComponent(),
														new DynamicPhysicsComponent(sf::FloatRect(2 * config.playerStartingX, config.playerStartingY, config.tileSize, config.tileSize), 0.05),
														new HumanoidGraphicsComponent(Textures::Elf_Red),
														new HumanoidCombatComponent(150, 150, 40, 130, 2),
														new HumanoidSocialComponent("Red Elf", "red_elves")  )) );
		mSpawnClock.restart();
	}

	if((sf::Keyboard::isKeyPressed(sf::Keyboard::F)) && (mSpawnClock.getElapsedTime().asSeconds() > 0.25)) {
		getGameObjects().push_back( *(new GameObject(	new BotActiveInputComponent(/*enemyControls*/),
														new DynamicPhysicsComponent(sf::FloatRect(3 * config.playerStartingX, config.playerStartingY, config.tileSize, config.tileSize), 0.03),
														new HumanoidGraphicsComponent(Textures::Elf_Yellow),
														new HumanoidCombatComponent(150, 150, 40, 130, 2),
														new HumanoidSocialComponent("Yellow Elf", "yellow_elves")  )) );
		mSpawnClock.restart();
	}


	//============UPDATING VIEW====================
	sf::Vector2f viewPosition;
	viewPosition.x = getGameObjects()[0].getPhysics()->getRect().left + config.tileSize / 2 - config.screenWidth / 2;
	viewPosition.y = getGameObjects()[0].getPhysics()->getRect().top + config.tileSize / 2 - config.screenHeight / 2;
		
	if(viewPosition.x < 0)														viewPosition.x = 0;
	if(viewPosition.x > getMapWidth() * config.tileSize - config.screenWidth)	viewPosition.x = getMapWidth() * config.tileSize - config.screenWidth;
	if(viewPosition.y < 0)														viewPosition.y = 0;
	if(viewPosition.y > getMapHeight() * config.tileSize - config.screenHeight)	viewPosition.y = getMapHeight() * config.tileSize - config.screenHeight;

	view.reset(sf::FloatRect(viewPosition.x, viewPosition.y, config.screenWidth, config.screenHeight));
	window.setView(view);


	//===============UPDATING HUD==================
	std::ostringstream hudHealth;
	//std::ostringstream hudMana;
	std::ostringstream hudEnemyCount;
	std::ostringstream hudPlayerCoordinates;
	std::ostringstream hudMouseCoordinates;

	hudHealth << getGameObjects()[0].getCombat()->getHP();
	//hudMana << getGameObjects()[0].getCombat()->getMP();
	hudEnemyCount << "Number of game objects: " << getGameObjects().size();
	hudPlayerCoordinates << "X: " << getGameObjects()[0].getPhysics()->getRect().left + config.tileSize / 2 << '\n'
						 << "Y: " << getGameObjects()[0].getPhysics()->getRect().top + config.tileSize / 2;
	hudMouseCoordinates << "X: " << sf::Mouse::getPosition(window).x << '\n'
						<< "Y: " << sf::Mouse::getPosition(window).y;

	//mTextMana.setString(hudMana.str());
	mTextHealth.setString(hudHealth.str());
	mTextEnemyCount.setString(hudEnemyCount.str());
	mTextPlayerCoordinates.setString(hudPlayerCoordinates.str());
	mTextMouseCoordinates.setString(hudMouseCoordinates.str());

	mTextHealth.setPosition(viewPosition.x, viewPosition.y);
	//textMana.setPosition(mViewPosition.x, mViewPosition.y + textMana.getCharacterSize());
	mTextEnemyCount.setPosition(viewPosition.x, viewPosition.y + mTextEnemyCount.getCharacterSize() * 2);
	mTextPlayerCoordinates.setPosition(viewPosition.x, viewPosition.y + mTextPlayerCoordinates.getCharacterSize() * 3);
	mTextMouseCoordinates.setPosition(viewPosition.x, viewPosition.y + mTextPlayerCoordinates.getCharacterSize() * 6);

}

void World::render(sf::RenderWindow& window, sf::View& view, config& config) {

	//Rendering level map tiles.
	for(int i = 0; i < getMapHeight(); ++i) {
		for(int j = 0; j < getMapWidth(); ++j) {
				
			switch(getLevelMap()[i][j]) {
				case 'B': mTile.setFillColor(sf::Color::Black); break;
				case '0': mTile.setFillColor(sf::Color::Green); break;
				default: continue;
			}

			mTile.setPosition(config.tileSize * j, config.tileSize * i);
			window.draw(mTile);
			//tile.setPosition(config.tileSize * j, config.tileSize * i);
			//window.draw(tile);

		}
	}

	//Rendering objects.
	for(int i = 0; i < getGameObjects().size(); ++i) 
		getGameObjects()[i].getGraphics()->draw(window);

	//Rendering HUD.
	window.draw(mTextHealth);
	//window.draw(mTextMana);
	window.draw(mTextEnemyCount);
	window.draw(mTextPlayerCoordinates);
	window.draw(mTextMouseCoordinates);
	
}

void World::resolveMapCollision(GameObject* object, int direction, int tileSize) {

	sf::FloatRect rect = object->getPhysics()->getRect();
	sf::Vector2f movement = object->getPhysics()->getMovement();

	for(int i = rect.top / tileSize; i < (rect.top + rect.height) / tileSize; ++i)
		for(int j = rect.left / tileSize; j < (rect.left + rect.width) / tileSize; ++j) {

			if(getLevelMap()[i][j] == 'B') {

				if((movement.x > 0) && (direction == 0)) {rect.left = j * tileSize - rect.width;	object->getInput()->setBadDirection(2);}
				if((movement.x < 0) && (direction == 0)) {rect.left = j * tileSize + tileSize;		object->getInput()->setBadDirection(4);}
				if((movement.y > 0) && (direction == 1)) {rect.top = i * tileSize - rect.height;	object->getInput()->setBadDirection(3);}
				if((movement.y < 0) && (direction == 1)) {rect.top = i * tileSize + tileSize;		object->getInput()->setBadDirection(1);}

			}

		}

	object->getPhysics()->setRect(rect);

}

void World::resolveObjectCollision(GameObject* object, int direction) {

	sf::FloatRect rect = object->getPhysics()->getRect();
	sf::Vector2f movement = object->getPhysics()->getMovement();

	for(int i = 0; i < getGameObjects().size(); ++i) {

		sf::FloatRect currentRect = getGameObjects()[i].getPhysics()->getRect();
		if((rect.intersects(currentRect)) && (object != &getGameObjects()[i])) {

			if((movement.x > 0) && (direction == 0)) {rect.left -= (rect.left + rect.width) - currentRect.left;			object->getInput()->setBadDirection(2);}
			if((movement.x < 0) && (direction == 0)) {rect.left += (currentRect.left + currentRect.width) - rect.left;	object->getInput()->setBadDirection(4);}
			if((movement.y > 0) && (direction == 1)) {rect.top -= (rect.top + rect.height) - currentRect.top;			object->getInput()->setBadDirection(3);}
			if((movement.y < 0) && (direction == 1)) {rect.top += (currentRect.top + currentRect.height) - rect.top;	object->getInput()->setBadDirection(1);}

		}

	}

	object->getPhysics()->setRect(rect);

}

void World::loadLevelMap(std::string filename) {

	std::ifstream inputFile(filename);

	int height;
	int width;

	inputFile >> height >> width;

	setMapHeight(height);
	setMapWidth(width);

	//Resizing the array.
	getLevelMap().resize(getMapHeight());
	for(int i = 0; i < getMapHeight(); ++i)
		getLevelMap()[i].resize(getMapWidth());

	inputFile.get();
	for(int i = 0; i < getMapHeight(); ++i) {
		for(int j = 0; j < getMapWidth(); ++j) {
			char temp = inputFile.get();
			getLevelMap()[i][j] = int(temp);
		}
		inputFile.get();
	}

	inputFile.close();

}

void World::deleteLevelMap() {

	getLevelMap().clear();
	getGameObjects().clear();

}
//
//==========================================