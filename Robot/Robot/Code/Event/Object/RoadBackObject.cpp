#include "RoadBackObject.h"


namespace
{
	const Size TEXTURE_SIZE(640, 320); // �摜�T�C�Y

	const Rect ROAD_TEXTURE_RECT    (0, 0, TEXTURE_SIZE);                     // ���̉摜�͈̔�
	const Rect ENTRANCE_TEXTURE_RECT(Point(0, 1)*TEXTURE_SIZE, TEXTURE_SIZE); // �����̉摜�͈̔�
	
	const String TEXTURE_NAME = L"Road"; // �摜�̖��O
}


Robot::RoadBackObject::RoadBackObject(const Point & pos)
	: EventObject(pos)
	, _scrollPx(0)
{
	_texture = 
	{
		TextureAsset(TEXTURE_NAME)(ROAD_TEXTURE_RECT),
		TextureAsset(TEXTURE_NAME)(ROAD_TEXTURE_RECT)
	};

	_initMap[L"Scroll"] = std::make_shared<Act>([this]() { _act = std::make_shared<Act>([this]() { scroll(); }); });

	_actMap[L"Entrance"] = std::make_shared<Act>([this]() { goEntrance(); });
}


void Robot::RoadBackObject::draw(const Vec2 &) const
{
	if (_isHidding) { return; }

	_texture.first.draw(-_scrollPx, 0);
	_texture.second.draw(-_scrollPx + TEXTURE_SIZE.x, 0);
}


void Robot::RoadBackObject::scroll()
{
	_scrollPx++;
	_scrollPx %= TEXTURE_SIZE.x;
}


void Robot::RoadBackObject::goEntrance()
{
	_scrollPx++;
	
	if (_scrollPx%TEXTURE_SIZE.x == 0)
	{
		_scrollPx = 0;
		_texture.second = TextureAsset(TEXTURE_NAME)(ENTRANCE_TEXTURE_RECT);
		_act = std::make_shared<Act>([this]() { stopEntrance(); });
	}
}


void Robot::RoadBackObject::stopEntrance()
{
	_scrollPx++;
	if (_scrollPx == TEXTURE_SIZE.x) 
	{ 
		finishAct();
	}
}
