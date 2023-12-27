#include"SkyMap.h"
#include"GameManager.h"
#include<vector>
#include "Terrains.h"
USING_NS_CC;
using namespace cocos2d::ui;

void SkyMap::loadPath() {

	float x, y;

	char namesize[10] = { 0 };
	for (int i = 1; i <= 41; i++) {
		sprintf(namesize, "p%d", i);
		ValueMap point = Point->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		path.push_back(Vec2(x, y));
	}
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "corner%d", i);
		ValueMap point = Corner->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		corner.push_back(Vec2(x, y));
	}
	ValueMap carrotloc = Object->getObject("carrot");
	x = carrotloc["x"].asFloat();
	y = carrotloc["y"].asFloat();
	corner.push_back(Vec2(x, y + 80));

}

void SkyMap::addTerrains()
{
	float x, y;
	char namesize[10] = { 0 };
	for (int i = 1; i <= towerNum; i++) {
		sprintf(namesize, "tower%d", i);
		ValueMap point = MyTerrain->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		terrains.push_back(Vec2(x, y));
	}

	for (int i = 0; i < towerNum; i++) {
		auto terrain = Terrains::createTerrain();
		terrain->setPosition(terrains.at(i));
		addChild(terrain, 0);
	}
}

void SkyMap::loadWave() {
	std::vector<std::vector<int>> skywave = {
		{fly,fly,fly,fly,fly,fly},
		{fly,fly,fly,fly,fly,fly}
	};

	for (size_t i = 0; i < skywave.size(); i++)
		waveMonster.push_back(skywave.at(i));

	maxWave = skywave.size();
}

SkyMap* SkyMap::createGame() {

	auto skymap = SkyMap::create();
	return skymap;

}

bool SkyMap::init() {
	if (!Scene::init())
		return false;

	GameManager::getGame()->init();

	tiledmap = TMXTiledMap::create("MAP/SKY/TileMap1.tmx");

	addChild(tiledmap, -1);
	if (tiledmap == nullptr)
		return false;

	GameManager::getGame()->Money = 1500;
	GameManager::getGame()->currentLevel = 1;

	loadWave();

	InitMap();

	addTerrains();

	loadPath();

	return true;

}
