#pragma once
class Achievement;
class AchievementList
{
public:
	AchievementList();
	virtual ~AchievementList();

	AchievementList(const AchievementList&) = delete;
	AchievementList& operator=(const AchievementList&) = delete;

	void Tick(double deltaTime);
	void Paint();

private:
	void Add();
	void BitmapLoad();
	void StringLoad();
	void Conditions();

	std::vector<Achievement*> m_AchievementArr;
	int m_CountTick = 0;
	int m_CountPaint = 0;

	// Achievement Bitmaps
	Bitmap* m_BmpAchievement1Ptr = nullptr;
	Bitmap* m_BmpAchievement2Ptr = nullptr;
	Bitmap* m_BmpAchievement3Ptr = nullptr;

	// Achievement Strings
	String m_StrAchievement1;
	String m_StrAchievement2;
	String m_StrAchievement3;
	
	// Condition Booleans
	bool m_BlAchievement1 = true;
	bool m_BlAchievement2 = true;
	bool m_BlAchievement3 = true;

};

