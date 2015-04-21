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
	RECT2 RectHealthBar();
	RECT2 RectNumber(int number);
	void SplitNum(int number);


	static const int HEALTH_WIDTH = 192;
	static const int HEALTH_HEIGHT = 24;
	static const int TEXT_SIZE = 24;
	Bitmap* m_HUDPtr = nullptr;

	int m_FirstNum = 0;
	int m_SecondNum = 0;

};

