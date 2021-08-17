#pragma once
#include "GameNode.h"

class Enemy;
class Tank : public GameNode
{
private:
	// 속성 : 멤버변수
	FPOINT pos;
	int size;
	float attackValue;
	string name;
	RECT shape;

	// 포신
	// 포신의 시작점, 끝점
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;		// 단위	: 도 (degree)		0	~ 180	~ 360
							//		: 라디안 (radian)	0f	~ 3.14f	~ 6.28f

	// 미사일
	int missileCount;

public:
	HRESULT Init();
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void RotateBarrel(float angle);
	void Move();
	void Fire();
	void FireSkill_01();
	void FireFollowTarget(Enemy* target);
	void Dead();

	// get, set
	FPOINT GetPos() { return this->pos; }
	int GetMissileCount() { return this->missileCount; }
};

