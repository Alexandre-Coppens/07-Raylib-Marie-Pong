#include "GolfBible.h"

enum class GolfType;
GolfBible* GolfBible::instance;
vector<vector<WavePart>> GolfBible::waves;

GolfBible::GolfBible(){
	//Need to make a function for that
	WavePart wavePart;
	vector<WavePart> wave;
	wavePart.golfType = GolfType::White;
	wavePart.numberOfEnemies = 20;
	wavePart.timeBtwEnemies = 0.5f;
	wavePart.timeBeforeNextPart = 5;
	wave.push_back(wavePart);
	waves.push_back(wave);
}

GolfBible::~GolfBible(){
}

Texture2D* GolfBible::GetGolfBallSkin(const GolfType golfType)
{
	return nullptr;
}

GolfBible* GolfBible::GetInstance() {
	if (instance == nullptr) {
		instance = new GolfBible();
	}
	return instance;
}