#include "UINewTower.h"
#include "Tower.h"
#include "Terrain.h"
#include <iostream>

using std::to_string;

UINewTower::UINewTower(TowerType _towerType):
	Actor(Vector2Zero(), Terrain::tileSize, ActorType::UINewTower),
	towerType(_towerType)
{
	sprite = TowerBible::GetTowerSkin(towerType);
}

UINewTower::~UINewTower(){
}

void UINewTower::Start(){
}

void UINewTower::Update(Vector2* scroll){
	position = GetMousePosition();
	CheckCanBePlaced(scroll);
	if (IsMouseButtonPressed(0)) PlaceTower(scroll);
}

void UINewTower::Draw(Vector2* scroll){
	Rectangle source{ 0, 0, sprite->width, sprite->height };
	Rectangle dest{ position.x, position.y, size.x, size.y };
	DrawTexturePro(*sprite, source, dest, Vector2{ size.x * 0.5f, size.y * 0.5f }, 0, color);
}

void UINewTower::PlaceTower(Vector2* scroll) {
	if (color.r == GREEN.r) {
		Vector2 mPos{ (int)floor((GetMouseX() + scroll->x) / Terrain::tileSize.x) * Terrain::tileSize.x + Terrain::tileSize.x * 0.5f, (int)floor((GetMouseY() + scroll->y) / Terrain::tileSize.y) * Terrain::tileSize.y + Terrain::tileSize.y * 0.5f };
		Actor::CreateActor("Tower_" + to_string((int)towerType) + "_" + to_string(std::rand()), 5, new Tower(mPos, Terrain::tileSize, towerType));
		Destroy();
	}
	else {
		std::cout << "Obstructed \n ";
	}
}

void UINewTower::CheckCanBePlaced(Vector2* scroll) {
	short isOnPath = 0; //0 = no, 1 = near a path, 2 = on a path
	Vector2 pathPosition;
	Vector2 mPos{ (int)floor((GetMouseX() + scroll->x) / Terrain::tileSize.x), (int)floor((GetMouseY() + scroll->y) / Terrain::tileSize.y) };
	vector<Terrain::Tile*> pathTiles = Terrain::GetEveryTilesWithModifier("Path");
	//Optimize This with the Tiles Directly
	for (int i = 0; i < pathTiles.size(); i++) {
		pathPosition = pathTiles[i]->position;
		if (Vector2Equals(pathPosition, mPos)) {
			isOnPath = 2;
			break;
		}
		else if (Vector2Equals(pathPosition, Vector2Add(mPos, Vector2{ 0, 1 }))) {
			isOnPath = 1;
		}
		else if (Vector2Equals(pathPosition, Vector2Add(mPos, Vector2{ 0, -1 }))) {
			isOnPath = 1;
		}
		else if (Vector2Equals(pathPosition, Vector2Add(mPos, Vector2{ 1, 0 }))) {
			isOnPath = 1;
		}
		else if (Vector2Equals(pathPosition, Vector2Add(mPos, Vector2{ -1, 0 }))) {
			isOnPath = 1;
		}
	}

	if (isOnPath == 2) {
		switch (towerType)
		{
		case TowerType::Windmill:
			color = GREEN;
			break;
		case TowerType::PirateBoat:
			color = RED;
			break;
		case TowerType::Dinosaur:
			color = RED;
			break;
		case TowerType::Volcano:
			color = GREEN;
			break;
		case TowerType::Moai:
			color = RED;
			break;
		default:
			color = RED;
			break;
		}
	}
	else if (isOnPath == 1) {
		switch (towerType)
		{
		case TowerType::Windmill:
			color = RED;
			break;
		case TowerType::PirateBoat:
			color = RED;
			break;
		case TowerType::Dinosaur:
			color = GREEN;
			break;
		case TowerType::Volcano:
			color = RED;
			break;
		case TowerType::Moai:
			color = GREEN;
			break;
		default:
			color = RED;
			break;
		}
	}
	else {
		switch (towerType)
		{
		case TowerType::Windmill:
			color = RED;
			break;
		case TowerType::PirateBoat:
			color = GREEN;
			break;
		case TowerType::Dinosaur:
			color = RED;
			break;
		case TowerType::Volcano:
			color = RED;
			break;
		case TowerType::Moai:
			color = RED;
			break;
		default:
			color = RED;
			break;
		}
	};

	Actor* ui = GetActorWithName("UIBackground");
	if (GetMouseX() >= ui->position.x && GetMouseX() <= ui->position.x + ui->size.x && GetMouseY() >= ui->position.y && GetMouseY() <= ui->position.y + ui->size.y) {
		color = RED;
	}
}