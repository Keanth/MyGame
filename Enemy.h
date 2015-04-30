#pragma once
#include "Hero.h"
#include "EnemyBase.h"

class Enemy : public EnemyBase
{
public:
	Enemy(LevelOutdoor* level, Hero* hero, DOUBLE2 position);
	virtual ~Enemy();

	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;
	
	virtual void Tick(double deltaTime);
	virtual void Paint();
};

