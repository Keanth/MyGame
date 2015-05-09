#pragma once
class SplashScreen
{
public:
	SplashScreen();
	~SplashScreen();

	SplashScreen(const SplashScreen&) = delete;
	SplashScreen& operator=(const SplashScreen&) = delete;

	void Tick(double deltaTime);
	void Paint();

private:
	void Transition(double time);

	Bitmap* m_BmpSplashScreenPtr = nullptr;
	
	double m_Opacity = 255;
	bool m_CountDown = false;
	bool m_CountUp = false;
};

