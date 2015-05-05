#include "stdafx.h"
#include "NightSpiritBullet.h"
#include "BitmapManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

int NightSpiritBullet::m_InstanceCounter = 0;

NightSpiritBullet::NightSpiritBullet(DOUBLE2 pos, int direction)
{
	m_BmpArrowPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Bullet.png"));
	m_HeroPos = pos;
	m_Direction = direction;

	Projectile::Init();
}

NightSpiritBullet::~NightSpiritBullet()
{
}

void NightSpiritBullet::Tick(double deltaTime)
{
	Projectile::Tick(deltaTime);
}

void NightSpiritBullet::Paint()
{
	Projectile::Paint();
}