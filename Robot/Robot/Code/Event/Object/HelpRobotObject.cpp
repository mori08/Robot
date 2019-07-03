#include "HelpRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(50, 100);                   // 拡大版の画像のサイズ
	const String ENLARGED_TEXTURE_NAME = L"HelpRobot(reduction)";  // 拡大版の画像の名前
	const Size   REDUCTION_TEXTURE_SIZE(50, 100);                  // 縮小版の画像のサイズ
	const String REDUCTION_TEXTURE_NAME = L"HelpRobot(reduction)"; // 縮小版の画像の名前
}


Robot::HelpRobotObject::HelpRobotObject(const Point & pos)
	: ChangeTextureObject(pos,Point::Zero,REDUCTION_TEXTURE_SIZE,REDUCTION_TEXTURE_NAME)
{
	_initMap[L"Reduction"] = std::make_shared<Act>([this]() { changeTextureName(REDUCTION_TEXTURE_SIZE, REDUCTION_TEXTURE_NAME); });
	_initMap[L"Enlarged"]  = std::make_shared<Act>([this]() { changeTextureName(ENLARGED_TEXTURE_SIZE , ENLARGED_TEXTURE_NAME ); });
}
