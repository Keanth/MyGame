#include "stdafx.h"
#include "HUD.h"
#include "Hero.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

HUD::HUD()
{
	m_HUDPtr = new Bitmap(String("./Assets/Images/HUD.png"));
}


HUD::~HUD()
{
	delete m_HUDPtr;
	m_HUDPtr = nullptr;
}

void HUD::Tick(double deltaTime)
{
}

void HUD::Paint()
{
	SplitNum(Hero::m_health);

	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());
	DOUBLE2 pos(10, 10);
	GAME_ENGINE->DrawBitmap(m_HUDPtr, pos, RectHealthBar());
	GAME_ENGINE->DrawBitmap(m_HUDPtr, DOUBLE2(35, 11), RectNumber(m_FirstNum));
	GAME_ENGINE->DrawBitmap(m_HUDPtr, DOUBLE2(58, 11), RectNumber(m_SecondNum));

}

RECT2 HUD::RectHealthBar()
{
	RECT2 r;

	r.top = 0;
	r.left = 0;

	r.bottom = r.top + HEALTH_HEIGHT;
	r.right = r.left + HEALTH_WIDTH;

	return r;
}
RECT2 HUD::RectNumber(int number)
{
	RECT2 r;
	r.top = TEXT_SIZE;
	r.left = number * TEXT_SIZE;

	r.bottom = TEXT_SIZE * 2;
	r.right = r.left + TEXT_SIZE;

	return r;
}

void HUD::SplitNum(int number)
{
	int digit = 0;
	if (number >= 0) {
		// Extract the digit
		digit = number % 10;

		// Manipulate the digit
		m_SecondNum = digit;

		// Reduce the number
		number /= 10;

		if (number >= 0)
		{
			// Extract the digit
			digit = number % 10;

			// Manipulate the digit
			m_FirstNum = digit;

			// Reduce the number
			number /= 10;
		}
	}
}