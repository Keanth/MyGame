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

	static const int FONT_HEIGHT = 16;
	static const int FONT_WIDTH = 160;

	int m_Pointer = 0;
	std::vector<String> m_MenuArr;

	Font* m_FntPixelFontPtr = nullptr;
	Bitmap* m_BmpFontPtr = nullptr;
	Bitmap* m_BmpFontSelectedPtr = nullptr;
	Bitmap* m_BmpBackgroundPtr = nullptr;
};

