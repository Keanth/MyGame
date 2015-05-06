#include "stdafx.h"
#include "NightSpiritBullet.h"
#include "BitmapManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

int NightSpiritBullet::m_InstanceCounter = 0;

NightSpiritBullet::NightSpiritBullet(DOUBLE2 pos, int direction)
{
	m_BmpArrowPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/SpriteSheet_Npc02.png"));
	m_HeroPos = pos;
	m_Direction = direction;

	m_BulletWidth = BULLET_WIDTH_NIGHTSPIRIT;
	m_BulletHeight = BULLET_HEIGHT_NIGHTSPIRIT;

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

RECT NightSpiritBullet::Rect()
{
	RECT r;

	int bulletwidth = m_BulletWidth / 2;

	r.top = m_BulletHeight * 3;
	r.left = bulletwidth * 9;
	r.bottom = m_BulletHeight + r.top;
	r.right = m_BulletWidth + r.left;

	return r;
}