#pragma once

class Exit
{
public:
	Exit();
	~Exit();

	Exit(const Exit&) = delete;
	Exit& operator=(const Exit&) = delete;

	void Tick(double deltaTime);
	void Paint();

private:
};

