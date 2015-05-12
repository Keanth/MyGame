#pragma once
class Achievement
{
public:
	Achievement(String text, Bitmap* bmp);
	virtual ~Achievement();

	Achievement(const Achievement&) = delete;
	Achievement& operator=(const Achievement&) = delete;

	void Tick(double deltaTime);
	void Paint();
	bool m_IsDone();

private:
	void AchievementBox(double deltaTime);
	void AchievementText(String &str);
	void AchievementPicture(Bitmap* &bmp);

	//AchievementBox
	Bitmap* m_BmpAchievementBoxPtr = nullptr;
	DOUBLE2 m_Pos;
	int m_PosY = 0;
	int m_PosCapY = 0;
	double m_Time = 0.0;
	bool m_TimeDone = false;

	Bitmap* m_BmpAchievementPicturePtr = nullptr;
	String m_AchievementText;

	bool m_Check = false;
};

