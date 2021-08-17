#pragma once
#include "Singleton.h"

class GameData : public Singleton <GameData>
{
private:
	int lastSceneID;

public:
	inline void SetLastSceneID(int lastSceneID) { this->lastSceneID = lastSceneID; }
	inline int GetLastSceneID() { return lastSceneID; }
};

