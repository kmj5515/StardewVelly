#pragma once
#include "config.h"
#include "Singleton.h"

class Image;
class Energy : public Singleton<Energy>
{
public :
	enum ENERGYWARNING { GREEN, YELLOW, RED };
private:
	Image* energyImg;

	POINT energyPos;
	RECT Egage;

	ENERGYWARNING energyWarning;

	int energySize;
	int useEnergy;

	bool resetEnergy;
	bool isGage;

	HBRUSH hBrush;
	HBRUSH hOldBrush;

	bool isTired;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void PlayerTired(bool isTired);

	inline void SetUseEnergy(int useEnergy) { this->useEnergy = useEnergy; }
	int GetUseEnergy() { return this->useEnergy; }

	inline void SetResetEnergy(bool resetEnergy) { this->resetEnergy = resetEnergy; }

	int GetIsTired() { return this->isTired; }

	virtual ~Energy() {};
};

