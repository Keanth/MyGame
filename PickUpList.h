#pragma once

class PickUpBase;
class Hero;
class PickUpList
{
public:
	PickUpList(Hero* Hero);
	virtual ~PickUpList();

	bool Add(PickUpBase* pickUpObj);
	void Remove();
	void RemoveAll();
	void Tick(double deltaTime);
	void Paint();
	void Hit();

private:
	std::vector<PickUpBase*> m_PickUpPtrArr;
	Hero* m_HeroPtr = nullptr;
};


