#include"../GameManager.h"


void Robot::GameObject::moveObject(const GameManager & gameManager,const Vec2 & vec)
{
	if (gameManager.isWalkingAblePos(_pos.movedBy(vec.x, 0)))
	{
		_pos.x += vec.x;
	}

	if (gameManager.isWalkingAblePos(_pos.movedBy(0, vec.y)))
	{
		_pos.y += vec.y;
	}
}
