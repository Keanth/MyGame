#pragma once
#include "EnemyBase.h"

class BulletList;
class NightSpirit : public EnemyBase
{
public:
	NightSpirit(LevelOutdoor* level, Hero* hero, DOUBLE2 position, BulletList* bulletList);
	virtual ~NightSpirit();
	
	NightSpirit(const NightSpirit&) = delete;
	NightSpirit& operator=(const NightSpirit&) = delete;

	virtual void Tick(double deltaTime);
	virtual void Paint();

protected:
	virtual void Init(LevelOutdoor* level, Hero* hero, DOUBLE2 position, BulletList* bulletList);
	virtual void MoveTowardHero(double deltaTime);
	virtual void Anim();
	virtual RECT Rect();
	virtual void Idle();
	virtual void Attack(double deltaTime);
	virtual void Shoot();

	bool m_AttackSpan = true;
	bool m_AttackSpanTimeWorthy = false;
	double m_AttackSpanTimer = 0.0;

	//Shoot
//	bool m_IsShootWorthy = true;
};

