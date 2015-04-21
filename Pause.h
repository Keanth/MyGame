#pragma once
class Pause
{
public:
	Pause();
	~Pause();

	Pause(const Pause&) = delete;
	Pause& operator=(const Pause&) = delete;

	void Tick(double deltaTime);
	void Paint();
};

