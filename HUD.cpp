#include "stdafx.h"
#include "HUD.h"
#include "Hero.h"
#include "PolarStarBullet.h"
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
	DOUBLE2 pos(10, 10);
	int posI = BAR_HEIGHT;
	int textPosY = int(pos.x + BAR_HEIGHT);

	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());

	GAME_ENGINE->DrawBitmap(m_HUDPtr, pos, RectExpBar());
	PaintExpBar(pos);
	pos.y += posI;
	GAME_ENGINE->DrawBitmap(m_HUDPtr, pos, RectHealthBar());
	GAME_ENGINE->DrawBitmap(m_HUDPtr, DOUBLE2(35, textPosY), RectNumber(m_FirstNum));
	GAME_ENGINE->DrawBitmap(m_HUDPtr, DOUBLE2(58, textPosY), RectNumber(m_SecondNum));

}

RECT2 HUD::RectExpBar()
{
	RECT2 r;

	r.top = BAR_HEIGHT * 3;
	r.left = 0;

	r.bottom = r.top + BAR_HEIGHT;
	r.right = r.left + BAR_WIDTH;

	return r;
}

void HUD::PaintExpBar(DOUBLE2 pos)
{
	COLOR lightYellow = COLOR(255, 248, 73);
	COLOR darkYellow = COLOR(255, 211, 89);
	COLOR brown = COLOR(62, 33, 0);

	DOUBLE2 posTopLeft = DOUBLE2(pos.x + BAR_OFFSET_X, pos.y + BAR_OFFSET_Y);;
	DOUBLE2 posRightBottom = DOUBLE2(posTopLeft.x + RECT_WIDTH, posTopLeft.y + RECT_HEIGHT);
	GAME_ENGINE->SetColor(lightYellow);
	GAME_ENGINE->FillRect(posTopLeft, posRightBottom);

	posTopLeft = DOUBLE2(pos.x + BAR_OFFSET_X, pos.y + BAR_OFFSET_Y);;
	posRightBottom = DOUBLE2(posTopLeft.x + RECT_WIDTH, posTopLeft.y + 2);
	GAME_ENGINE->SetColor(darkYellow);
	GAME_ENGINE->FillRect(posTopLeft, posRightBottom);

	posTopLeft = DOUBLE2(pos.x + BAR_OFFSET_X, pos.y + BAR_OFFSET_Y + 11);;
	posRightBottom = DOUBLE2(posTopLeft.x + RECT_WIDTH, posTopLeft.y + 2);
	GAME_ENGINE->SetColor(darkYellow);
	GAME_ENGINE->FillRect(posTopLeft, posRightBottom);

	posTopLeft = DOUBLE2(pos.x + BAR_OFFSET_X, pos.y + BAR_OFFSET_Y + 13);;
	posRightBottom = DOUBLE2(posTopLeft.x + RECT_WIDTH, posTopLeft.y + 2);
	GAME_ENGINE->SetColor(brown);
	GAME_ENGINE->FillRect(posTopLeft, posRightBottom);
}

RECT2 HUD::RectHealthBar()
{
	RECT2 r;

	r.top = 0;
	r.left = 0;

	r.bottom = r.top + BAR_HEIGHT;
	r.right = r.left + BAR_WIDTH;

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