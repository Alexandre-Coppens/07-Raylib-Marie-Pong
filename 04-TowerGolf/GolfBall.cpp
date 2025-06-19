#include <iostream>
#include <fstream>
#include "GolfBall.h"

using std::ofstream;
using std::ifstream;

using std::to_string;
using std::cout;

GolfBall::GolfBall() {
}

GolfBall::GolfBall(Vector2 _pos, Vector2 _size, Color _color) {
	sprite = &AssetList::SpriteList["Unknown"];
	position = _pos;
	size = _size;
	color = _color;
	type = GameObjectType::GolfBall;
	CreateRect();
}

GolfBall::~GolfBall() {
}

void GolfBall::Start() {
	//Calculate a path to the end, NEED TO PUT ON THE SPAWNER AND NOT THE BALL;
	startPos = Terrain::GetEveryTilesWithModifier("Spawn")[0]->position;
	vector<Terrain::Tile*> pathTiles = Terrain::GetEveryTilesWithModifier("Path");
	pathTiles.push_back(Terrain::GetEveryTilesWithModifier("End")[0]);

	CreatePaths(pathTiles, vector<Vector2> {startPos});

	startPos.x = (startPos.x + 0.5f) * Terrain::tileSize.x;
	startPos.y = (startPos.y + 0.5f) * Terrain::tileSize.y;
	position = startPos;

	currentPath = GetRandomValue(0, 2);
}

void GolfBall::Update(Vector2* scroll) {
	Vector2 next = Vector2Add(Vector2Multiply(path[currentPath][currentTile], Terrain::tileSize), Vector2Multiply(Terrain::tileSize, Vector2{ 0.5f, 0.5f }));
	position = Vector2MoveTowards(position, next, speed * GetFrameTime());
	if (Vector2Distance(position, next) < 0.1f) {
		currentTile++;
	}
	//cout << Vector2Distance(position, next) << "\n";
}

void GolfBall::Draw(Vector2* scroll) {
	Rectangle source{0, 0, sprite->width, sprite->height};
	Rectangle dest{position.x - scroll->x, position.y - scroll->y, size.x, size.y};
	DrawTexturePro(*sprite, source, dest, Vector2{size.x * 0.5f, size.y * 0.5f}, 0, color);
}

void GolfBall::CreatePaths(vector<Terrain::Tile*> pathTiles, vector<Vector2> currentPath) {
	if (pathTiles.size() == 0) return;
	Vector2 currentTile = currentPath[currentPath.size() - 1];
	for (int i = 0; i < pathTiles.size(); i++) {
		if ((pathTiles[i]->position.x == currentTile.x + 1 && currentTile.y == pathTiles[i]->position.y) ||
			(pathTiles[i]->position.x == currentTile.x - 1 && currentTile.y == pathTiles[i]->position.y) ||
			(pathTiles[i]->position.x == currentTile.x && currentTile.y + 1 == pathTiles[i]->position.y) ||
			(pathTiles[i]->position.x == currentTile.x && currentTile.y - 1 == pathTiles[i]->position.y)) {

			currentPath.push_back(pathTiles[i]->position);
			if (Terrain::dictionary[pathTiles[i]->dictionaryTexture] == "End") {
				path.push_back(currentPath);
				return;
			}
			
			vector<Terrain::Tile*> pathLeft = pathTiles;
			pathLeft.erase(pathLeft.begin() + i);
			CreatePaths(pathLeft, currentPath);
			currentPath.pop_back();
		}
	}
	return;
}