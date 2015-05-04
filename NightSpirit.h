#pragma once
#include "EnemyBase.h"

class NightSpirit : public EnemyBase
{
public:
	NightSpirit(LevelOutdoor* level, Hero* hero, DOUBLE2 position);
	virtual ~NightSpirit();
	
	NightSpirit(const NightSpirit&) = delete;
	NightSpirit& operator=(const NightSpirit&) = delete;

	virtual void Tick(double deltaTime);
	virtual void Paint();

protected:
	virtual void Init(LevelOutdoor* level, Hero* hero, DOUBLE2 position);
	virtual void MoveTowardHero(double deltaTime);
	virtual void Anim();
	virtual RECT Rect();
};

