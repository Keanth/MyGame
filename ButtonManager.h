#pragma once
class ButtonManager
{
public:
	ButtonManager(DOUBLE2 position);
	virtual ~ButtonManager();

	ButtonManager(const ButtonManager&) = delete;
	ButtonManager& operator=(const ButtonManager&) = delete;

	void Tick(double deltaTime);
	void Paint();
	bool CheckIsHit(POINT p);

	static const int BUTTON_WIDTH = 100;
	static const int BUTTON_HEIGHT = 30;

private:
	DOUBLE2 m_Position;
	PhysicsActor* m_ActIsOnPtr = nullptr;
	int m_HitCntr = 0;
};

