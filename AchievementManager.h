#pragma once
class AchievementManager
{
public:
	AchievementManager();
	virtual ~AchievementManager();

	AchievementManager(const AchievementManager&) = delete;
	AchievementManager& operator=(const AchievementManager&) = delete;

	void Tick(double deltaTime);
	void Paint();

private:
	void AchievementBox(double deltaTime);
	void AchievementText(String &str);
	void AchievementPicture(Bitmap* &bmp);
	bool Conditions(int number);

	//AchievementBox
	Bitmap* m_BmpAchievementBoxPtr = nullptr;
	DOUBLE2 m_Pos;
	int m_PosY = 0;
	int m_PosCapY = 0;
	double m_Time = 0.0;
	bool m_TimeDone = false;
	bool m_AchievementChecked = false;

	Bitmap* m_BmpAchievementPicturePtr = nullptr;

	int _int = 0;
};

