#include "GolfWaveSystem.h"
#include "GolfBall.h"

using std::to_string;

GolfWaveSystem::GolfWaveSystem(){
}

GolfWaveSystem::~GolfWaveSystem(){
}

void GolfWaveSystem::Start() {
	GolfBible::GetInstance();

	startPos = Terrain::GetEveryTilesWithModifier("Spawn")[0]->position;
	vector<Terrain::Tile*> pathTiles = Terrain::GetEveryTilesWithModifier("Path");
	pathTiles.push_back(Terrain::GetEveryTilesWithModifier("End")[0]);

	CreatePaths(pathTiles, vector<Vector2> {startPos});

	startPos.x = (startPos.x + 0.5f) * Terrain::tileSize.x;
	startPos.y = (startPos.y + 0.5f) * Terrain::tileSize.y;
}

void GolfWaveSystem::Update(Vector2* scroll) {
	if (canSpawnWave) SpawnWave();
	vector<Actor*> ballsLeft = GetAllActorsWith(ActorType::GolfBall);
	if (ballsLeft.size() == 0) {
		canSpawnWave = true;
		currentPart = 0;
		if(currentWave != GolfBible::waves.size() - 1)currentWave++;
		timer = 99;
	}
}

void GolfWaveSystem::Draw(Vector2* scroll) {
	Actor::Draw(scroll);
}

void GolfWaveSystem::CreatePaths(vector<Terrain::Tile*> pathTiles, vector<Vector2> currentPath) {
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

void GolfWaveSystem::SpawnWave() {
	if (currentSpawnNbr < GolfBible::waves[currentWave][currentPart].numberOfEnemies) {
		if (timer >= GolfBible::waves[currentWave][currentPart].timeBtwEnemies) {
			timer = 0;
			currentSpawnNbr++;
			CreateGolfBall(GolfBible::waves[currentWave][currentPart].golfType);
		}
		else {
			timer += GetFrameTime();
		}
	}
	else {
		if (timer >= GolfBible::waves[currentWave][currentPart].timeBeforeNextPart) {
			timer = 0;
			currentSpawnNbr = 0;
			currentPart++;
			if(currentPart == GolfBible::waves[currentWave].size())canSpawnWave = false;
		}
		else {
			timer += GetFrameTime();
		}
	}
}

void GolfWaveSystem::CreateGolfBall(GolfType golfType) {
	GolfBall* pGolfBall{};
	int r = currentSpawnNbr % path.size();
	switch (golfType)
	{
	case GolfType::White:
		pGolfBall = static_cast<GolfBall*>(Actor::CreateActor("GolfWhite" + to_string(std::rand()), 3, new GolfBall(startPos, Vector2{ 20,20 }, GolfType::White, WHITE)));
		break;
	case GolfType::Red:
		pGolfBall = static_cast<GolfBall*>(Actor::CreateActor("GolfRed" + to_string(std::rand()), 3, new GolfBall(startPos, Vector2{ 20,20 }, GolfType::Red, WHITE)));
		break;
	case GolfType::Metal:
		break;
	case GolfType::Fire:
		break;
	case GolfType::Boss:
		break;
	}
	if(pGolfBall != nullptr) pGolfBall->SetPath(path[r], 1);
	pGolfBall = NULL;
	delete pGolfBall;
}