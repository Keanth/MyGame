#pragma once

class PickUpBase;
class PickUpList
{
public:
	PickUpList();
	virtual ~PickUpList();

	bool Add(PickUpBase* pickUpObj);
	bool Remove(PickUpBase* pickUpObj);
	void RemoveAll();
	void Tick(double deltaTime);
	void Paint();
	void Hit();

private:
	std::vector<PickUpBase*> m_PickUpPtrArr;
};


