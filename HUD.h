#pragma once
class HUD
{
public:
	HUD();
	virtual ~HUD();

	HUD(const HUD&) = delete;
	HUD& operator=(const HUD&) = delete;

	void Tick(double deltaTime);
	void Paint();

private:
	RECT2 RectExpBar();
	void PaintExpBar(DOUBLE2 pos);
	RECT2 RectHealthBar();
	RECT2 RectNumber(int number);
	void SplitNum(int number);


	const int BAR_WIDTH = 192;
	const int BAR_HEIGHT = 24;
	const int TEXT_SIZE = 24;
	const int BAR_OFFSET_X = 72;
	const int BAR_OFFSET_Y = 3;
	const int RECT_WIDTH = 117;
	const int RECT_HEIGHT = 15;

	Bitmap* m_HUDPtr = nullptr;

	int m_FirstNum = 0;
	int m_SecondNum = 0;

};

