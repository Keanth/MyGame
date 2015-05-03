#pragma once
#include "EnemyBase.h"

class GraveKeeper : public EnemyBase
{
public:
	GraveKeeper(LevelOutdoor* level, Hero* hero, DOUBLE2 position);
	virtual ~GraveKeeper();

	GraveKeeper(const GraveKeeper&) = delete;
	GraveKeeper& operator=(const GraveKeeper&) = delete;
	
	virtual void Tick(double deltaTime);
	virtual void Paint();

protected:
	virtual void Init(LevelOutdoor* level, Hero* hero, DOUBLE2 position);
	virtual void MoveTowardHero(double deltaTime);
	virtual void UpdateVariables(double deltaTime);
};

