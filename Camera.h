#pragma once
class Hero;
class LevelOutdoor;
class Camera
{
public:
	Camera(Hero* heroPtr);
	virtual ~Camera();
	// C++11 make the class non-copyable
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	MATRIX3X2 GetPlayerMatrix();
	MATRIX3X2 GetViewMatrix();
	
	void Tick(double deltaTime);
	//getters
	DOUBLE2 GetCamPos();
	double GetCamScale();

private:
	static const int CAM_MOVEMENT = 10;

	Hero* m_HeroPtr = nullptr;

	static const int MAXLEFT = 25;
	static const int MAXRIGHT = -15;
	double m_CameraScale = 0.8;
	double m_CameraAngle = 0.0;
	DOUBLE2 m_CamPos = DOUBLE2(0, 0);
	DOUBLE2 m_CameraDimension;
};

