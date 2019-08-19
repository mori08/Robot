#include"../GameManager.h"


void Robot::GameObject::moveObject(const Vec2 & vec)
{
	if (GameManager::Instance().isWalkingAblePos(_pos.movedBy(vec.x, 0)))
	{
		_pos.x += vec.x;
	}

	if (GameManager::Instance().isWalkingAblePos(_pos.movedBy(0, vec.y)))
	{
		_pos.y += vec.y;
	}
}
