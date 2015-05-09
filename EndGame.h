#pragma once
class EndGame
{
public:
	EndGame();
	virtual ~EndGame();

	EndGame(const EndGame&) = delete;
	EndGame& operator=(const EndGame&) = delete;

	void Tick(double deltaTime);
	void Paint();

private:
	void ExitBox();

	int m_Pointer = 1;
	std::vector<String> m_EndGameArr;

	Bitmap* m_BmpYesPtr = nullptr;
	Bitmap* m_BmpNoPtr = nullptr;
};