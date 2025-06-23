#include "GolfBible.h"

enum class GolfType;
GolfBible* GolfBible::instance;
vector<vector<WavePart>> GolfBible::waves;

GolfBible::GolfBible(){
	vector<WavePart> wave;

	wave.push_back(MakeWavePart(GolfType::White, 20, 0.5f, 10));
	waves.push_back(wave);

	wave.clear();
	wave.push_back(MakeWavePart(GolfType::White, 20, 0.25f, 2));
	wave.push_back(MakeWavePart(GolfType::Red, 10, 0.5f, 10));
	waves.push_back(wave);
}

GolfBible::~GolfBible(){
}

Texture2D* GolfBible::GetGolfBallSkin(const GolfType golfType)
{
	return nullptr;
}

int GolfBible::GetGolfBallDamages(const GolfType golfType)
{
	switch (golfType)
	{
	case (GolfType::White):
		return 1;
	case (GolfType::Red):
		return 4;
	case (GolfType::Metal):
		return 16;
	case (GolfType::Fire):
		return 12;
	case (GolfType::Boss):
		return 100;
	default:
		return 1;
	}
}

GolfBallsStats GolfBible::GetGolfBallStats(const GolfType golfType)
{
	switch (golfType)
	{
	case (GolfType::White):
		return GolfBallsStats{50, 1, 0};
	case (GolfType::Red):
		return GolfBallsStats{ 75, 1, 3 };
	case (GolfType::Metal):
		break;
	case (GolfType::Fire):
		break;
	case (GolfType::Boss):
		break;
	default:
		break;
	}
}

GolfBible* GolfBible::GetInstance() {
	if (instance == nullptr) {
		instance = new GolfBible();
	}
	return instance;
}

WavePart GolfBible::MakeWavePart(GolfType golfType, uint16_t numberOfEnemies, float timeBtwEnemies, float timeBfNextPart) {
	return WavePart{ golfType, numberOfEnemies, timeBtwEnemies, timeBfNextPart };
}