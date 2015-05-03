#include "stdafx.h"
#include "PolarStarBullet.h"
#include "BitmapManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

int PolarStarBullet::m_InstanceCounter = 0;
int PolarStarBullet::m_Exp = INITIAL_EXP;

PolarStarBullet::PolarStarBullet(DOUBLE2 pos, int direction)
{
	m_BmpArrowPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Bullet.png"));
	m_HeroPos = pos; 
	m_Direction = direction;

	Projectile::Init();
}

PolarStarBullet::~PolarStarBullet()
{
}

void PolarStarBullet::Tick(double deltaTime)
{
	Projectile::Tick(deltaTime);
}

void PolarStarBullet::Paint()
{
	Projectile::Paint();
}