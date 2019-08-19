#include "TestGameObject.h"
#include "../../MyColor.h"


namespace
{
	const Vec2 GENERATE_POS(10,10);
}


Robot::TestGameObject::TestGameObject()
	: GameObject(GENERATE_POS)
{
}


void Robot::TestGameObject::update()
{
	_pos += GameManager::Instance().getPath(_pos, Mouse::PosF());
}


void Robot::TestGameObject::draw() const
{
	Circle(_pos, 10).draw(Palette::MyBlack);
}
