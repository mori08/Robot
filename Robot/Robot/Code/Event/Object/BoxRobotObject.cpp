#include "BoxRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(60,60);                    // 拡大版の画像のサイズ
	const String ENLARGED_TEXTURE_NAME = L"BoxRobot(reduction)";  // 拡大版の画像の名前
	const Size   REDUCTION_TEXTURE_SIZE(30, 30);                  // 縮小版の画像のサイズ
	const String REDUCTION_TEXTURE_NAME = L"BoxRobot(reduction)"; // 縮小版の画像の名前
}


Robot::BoxRobotObject::BoxRobotObject(const Point & pos)
	: EventObject(pos)
	, _textureSize(REDUCTION_TEXTURE_SIZE)
	, _textureName(REDUCTION_TEXTURE_NAME)
	, _texturePos(Point::Zero)
{
	_initMap[L"Reduction"] = std::make_shared<Act>([this]() { reduction(); });
	_initMap[L"Enlarged"]  = std::make_shared<Act>([this]() { enlarged(); });
}


void Robot::BoxRobotObject::draw(const Vec2 & shakeSize) const
{
	TextureAsset(_textureName)(_texturePos*_textureSize, _textureSize).draw(_pos + shakeSize);
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
