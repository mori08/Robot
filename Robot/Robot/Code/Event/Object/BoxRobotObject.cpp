#include "BoxRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE;
	const String ENLARGED_TEXTURE_NAME;
	const Size   REDUCTION_TEXTURE_SIZE(30, 30);                  // 縮小版の画像のサイズ
	const String REDUCTION_TEXTURE_NAME = L"BoxRobot(reduction)"; // 縮小版の画像の名前
}


Robot::BoxRobotObject::BoxRobotObject(const Point & pos)
	: EventObject(pos)
	, _textureSize(REDUCTION_TEXTURE_SIZE)
	, _textureName(REDUCTION_TEXTURE_NAME)
{
	
}


void Robot::BoxRobotObject::draw(const Vec2 & shakeSize) const
{
}


void Robot::BoxRobotObject::reduction()
{
	_textureSize = REDUCTION_TEXTURE_SIZE;
	_textureName = REDUCTION_TEXTURE_NAME;
}


void Robot::BoxRobotObject::enlarged()
{
	_textureSize = ENLARGED_TEXTURE_SIZE;
	_textureName = ENLARGED_TEXTURE_NAME;
}
