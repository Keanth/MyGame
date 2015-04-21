#pragma once
class Entity
{
public:
	Entity();
	virtual ~Entity();

	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

private:

};

