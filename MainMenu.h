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
	void RemoveButton();
	
	static const int _buttonWidth = 100;
	static const int _buttonHeight = 30;
	
	Button* _button = nullptr;
	bool m_ButtonIsRemoved = false;

};

