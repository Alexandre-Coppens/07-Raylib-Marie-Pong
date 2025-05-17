#include "Terrain.h"

map<int, string> Terrain::dictionary;
vector<vector<Terrain::Tile>> Terrain::terrain;
Vector2 Terrain::tileSize{ 50,50 };
Vector2 Terrain::position{ 0,0 };

Terrain::Terrain() {
}

Terrain::~Terrain(){
}

void Terrain::Update()
{
}

void Terrain::AddNewTile(Vector2 pos, string name){
	if (terrain.empty()) terrain.push_back(vector<Tile>());
	for (auto d : dictionary) {
		if (name == d.second) {
			terrain[0].push_back(Tile{ pos, 0, 0, d.first });
			return;
		}
	}

	int newInt = (int)dictionary.size();
	terrain[0].push_back(Tile{ pos, 0, 0, newInt});
	dictionary[newInt] = name;
}

void Terrain::RemoveTile(){
}
