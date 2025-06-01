#include <iostream>
#include <fstream>
#include "Car.h"
#include "Terrain.h"

using std::ofstream;
using std::ifstream;

using std::to_string;
using std::cout;

Car::Car(){
}

Car::Car(Vector2 _pos, Vector2 _size, Color _color){
	sprite = &AssetList::SpriteList["SpriteSheet_Car"];
	position = _pos;
	size = _size;
	color = _color;
	type = GameObjectType::Car;
	CreateRect();
	LoadScore();
}

Car::~Car(){
}

void Car::Update(Vector2* scroll){
	towardSpeed = 0;
	isAccelerating = false;

	if (IsKeyDown(KEY_UP)) {
		towardSpeed = maxSpeed.x ;
		isAccelerating = true;
	}
	else if (IsKeyDown(KEY_DOWN)) {
		towardSpeed = maxSpeed.y;
		isAccelerating = true;
	}
	if (IsKeyDown(KEY_LEFT) && abs(speed) >= minTurnSpeed ) {
		rotation += turnRate * PI * GetFrameTime();
	}
	if (IsKeyDown(KEY_RIGHT) && abs(speed) >= minTurnSpeed) {
		rotation -= turnRate * PI * GetFrameTime();
	}

	speed = Lerp(speed, towardSpeed, (isAccelerating ? thrust : decay) * GetFrameTime());

	deltaSpeed.x = sin(rotation) * -speed * GetFrameTime();
	deltaSpeed.y = cos(rotation) * -speed * GetFrameTime();

	position.x += deltaSpeed.x;
	position.y += deltaSpeed.y;

	currentTimer += GetFrameTime();

	Vector2 tilePos{ (int)floor((position.x + size.x * 0.5f) / (Terrain::tileSize.x)), (int)floor((position.y + size.y * 0.5f) / (Terrain::tileSize.y)) };
	for (int i = Terrain::terrain.size()-1; i >= 0; i--) {
		for (auto i : Terrain::terrain[i]) {
			if (Vector2Equals(i.position, tilePos)) {
				if (i.modifier == "Tires") {
					position.x -= deltaSpeed.x;
					position.y -= deltaSpeed.y;
				}
				if (i.modifier == "Grass") {
					position.x -= deltaSpeed.x * 0.5f;
					position.y -= deltaSpeed.y * 0.5f;
				}
				if (i.modifier == "Checkpoint") {
					int checkpoint = stoi(Terrain::BreakString(Terrain::dictionary[i.dictionaryTexture], '_')[1]);
					if (checkpoint == currentCheckpoint + 1) currentCheckpoint ++;
				}
				if (i.modifier == "FinishLine") {
					if (currentCheckpoint == maxCheckpoint) {
						currentCheckpoint = 0;
						if (currentTimer < bestTimer) bestTimer = currentTimer;
						currentTimer = 0;
						SaveScore();
						cout << "Finished Lap!! \n";
					}
				}
				return;
			}
		}
	}
}

void Car::Draw(Vector2* scroll) {
	CarSide();
	Vector2 posInSprite{ 
		sprite->width * currentSprite.x * 0.33f , 
		sprite->height * currentSprite.y * 0.33f 
	};

	Rectangle source = { posInSprite.x, posInSprite.y, sprite->width * 0.33f * ((flipX || speed < 0) && !(!flipX && speed < 0) ? -1 : 1), sprite->height * 0.33f};
	Rectangle dest = { position.x - scroll->x, position.y - scroll->y, size.x, size.y };
	DrawTexturePro(*sprite, source, dest, Vector2Zero(), 0, color);

	DrawTextPro(AssetList::textFont["jupiter_crash"], (to_string((int)currentTimer / 60) + " : " + to_string((int)currentTimer % 60) + "." + to_string((int)((currentTimer - floor(currentTimer)) * 100))).c_str(), Vector2{ 200, 0 }, Vector2{ 0,0 }, 0, 50, 5, DARKGRAY);
	DrawTextPro(AssetList::textFont["jupiter_crash"], (to_string((int)bestTimer / 60) + " : " + to_string((int)bestTimer % 60) + "." + to_string((int)((bestTimer - floor(bestTimer))*100))).c_str(), Vector2{200, 50}, Vector2{0,0}, 0, 50, 5, ORANGE);
	
	//DrawText(to_string(speed).c_str(), 10, 10, 20, GRAY);
	//Vector2 tilePos{ (int)floor((position.x + size.x * 0.5f) / (Terrain::tileSize.x)), (int)floor((position.y + size.y * 0.5f) / (Terrain::tileSize.y)) };
	//DrawRectangle(tilePos.x * Terrain::tileSize.x - scroll->x, tilePos.y * Terrain::tileSize.y - scroll->y, 5, 5, MAGENTA);
}

void Car::CarSide() {
	Vector2 ndeltaSpeed = Vector2Normalize(deltaSpeed);
	 float dot = Vector2DotProduct( ndeltaSpeed, Vector2{0,1});
	 dot += 1;
	 dot *= 0.5f;
	 dot *= 8;
	 const int idot = static_cast<int>(dot + 0.5f);
	 currentSprite = { static_cast<float>(idot % 3), static_cast<float>(idot / 3) };

	 flipX = Vector2DotProduct(ndeltaSpeed, Vector2{ 1,0 }) <= 0;
}

void Car::SaveScore() {
	ofstream saveFile;
	saveFile.open("HighScore_CarGame.txt");
	if (saveFile.is_open()) {
		saveFile << "H$" + to_string(bestTimer) + "\n";
		saveFile.close();
	}
	else {
		cout << "Could not load  HighScore_CarGame.txt \n";
	}
}

void Car::LoadScore() {
	string line;
	ifstream loadFile("HighScore_CarGame.txt");

	if (loadFile.is_open()) {
		while (getline(loadFile, line)) {
			if (line[0] == 'H') {
				vector<string> l = Terrain::BreakString(line, '$');;
				bestTimer = stof(l[1]);
			}
		}
		loadFile.close();
	}
	else {
		cout << "Could not load  HighScore_CarGame.txt \n";
	}
}