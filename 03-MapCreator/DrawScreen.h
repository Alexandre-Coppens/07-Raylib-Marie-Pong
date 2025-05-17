#pragma once

#include <vector>
#include "Raylib.h"
#include "AssetsList.h"
#include "GameObject.h"
#include "Terrain.h"

using std::vector;

static void DrawScreen(Vector2* scroll);

//Draw the terrain and the gameObjects on screen
static void DrawScreen(Vector2* scroll){
	vector<vector<GameObject*>>* goList = GameObject::GetAllGameObjectsLayered();
	vector<vector<Terrain::Tile>>* terrain = &Terrain::terrain;

	short max = fmax(terrain->size(), goList->size());
	for (int i = 0; i < max; i++) {
		if (!terrain->size() <= i) {
			for (Terrain::Tile tile : (*terrain)[i]) {
				Texture2D* sprite = &AssetList::SpriteList[Terrain::dictionary[tile.dictionaryTexture]];
				DrawTexturePro(*sprite,
					Rectangle{ 0, 0, (float)sprite->width, (float)sprite->height },
					Rectangle{ scroll->x +(tile.position.x *Terrain::tileSize.x), scroll->y + (tile.position.y * Terrain::tileSize.y), Terrain::tileSize.x, Terrain::tileSize.y },
					Vector2{ 0,0 },
					tile.rotation,
					WHITE);
			}
		}

		if (!goList->size() <= i) {
			for (GameObject* go : (*goList)[i]) {
				if (go->enabled) go->Draw(*scroll);
			}
		}
	}
}