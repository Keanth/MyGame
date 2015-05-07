#pragma once

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	MainMenu(const MainMenu&) = delete;
	MainMenu& operator=(const MainMenu&) = delete;

	void Tick(double deltaTime);
	void Paint();

private:
	RECT2 Rect(int number);
	void Menu();
	void Background(int number, double deltaTime);
	void BackgroundPaint();
	void BackgroundLoop();

	static const int FONT_HEIGHT = 16;
	static const int FONT_WIDTH = 160;

	double m_Count = 0.0;
	bool m_Menu = false;

	int m_Pointer = 0;
	std::vector<String> m_MenuArr;

	Font* m_FntPixelFontPtr = nullptr;
	Bitmap* m_BmpFontPtr = nullptr;
	Bitmap* m_BmpFontSelectedPtr = nullptr;

	//BG
	Bitmap* m_BmpBackgroundPtr = nullptr;
	Bitmap* m_BmpLevelOutdoor1Ptr = nullptr;
	Bitmap* m_BmpLevelOutdoor2Ptr = nullptr;
	Bitmap* m_BmpLevelOutdoor3Ptr = nullptr;
	Bitmap* m_BmpLevelOutdoor4Ptr = nullptr;

	DOUBLE2 m_Pos1;
	DOUBLE2 m_Pos2;
	DOUBLE2 m_Pos3;
	DOUBLE2 m_Pos4;

	DOUBLE2 m_Pos12;
	DOUBLE2 m_Pos22;
	DOUBLE2 m_Pos32;
	DOUBLE2 m_Pos42;

	int m_BitmapWidth = 0;

};

