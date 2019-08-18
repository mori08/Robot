#include "RoadBackObject.h"


namespace
{
	const Size TEXTURE_SIZE(640, 320); // 画像サイズ

	const Rect ROAD_TEXTURE_RECT    (0, 0, TEXTURE_SIZE);                     // 道の画像の範囲
	const Rect ENTRANCE_TEXTURE_RECT(Point(0, 1)*TEXTURE_SIZE, TEXTURE_SIZE); // 入口の画像の範囲
	
	const String TEXTURE_NAME = L"Road"; // 画像の名前
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

	_initMap[L"Entrance"] = std::make_shared<Act>([this]() { _act = std::make_shared<Act>([this]() { startEntrance(); }); });
	_initMap[L"Scroll"]   = std::make_shared<Act>([this]() { _act = std::make_shared<Act>([this]() { scroll();        }); });

	_actMap[L"Entrance"] = std::make_shared<Act>([this]() { goEntrance(); });
}


void Robot::RoadBackObject::draw(const Vec2 & shakeSize) const
{
	_texture.first .draw(Vec2(-_scrollPx                 , 0) + shakeSize);
	_texture.second.draw(Vec2(-_scrollPx + TEXTURE_SIZE.x, 0) + shakeSize);
}


void Robot::RoadBackObject::startEntrance()
{
	_act = noAct;
	_scrollPx = 0;
	_texture.first = TextureAsset(TEXTURE_NAME)(ENTRANCE_TEXTURE_RECT);
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
