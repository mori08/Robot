#include "HelpRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(100, 200);                   // 拡大版の画像のサイズ
	const String ENLARGED_TEXTURE_NAME = L"HelpRobot(enlarged)";  // 拡大版の画像の名前
	const Size   REDUCTION_TEXTURE_SIZE(50, 100);                  // 縮小版の画像のサイズ
	const String REDUCTION_TEXTURE_NAME = L"HelpRobot(reduction)"; // 縮小版の画像の名前

	const size_t             ARM_SPAN = 10;           // 腕を動かす動きの画像を切り替えるフレームの間隔
	const std::vector<Point> ARMUP_TEXTURE_POS_LIST   // 腕を上がる動きの画像のリスト
	{ Point(0,0),Point(1,0),Point(2,0) };
	const std::vector<Point> ARMDOWN_TEXTURE_POS_LIST // 腕を下げる動きの画像のリスト
	{ Point(2,0),Point(1,0),Point(0,0) };
}


Robot::HelpRobotObject::HelpRobotObject(const Point & pos)
	: ChangeTextureObject(pos,Point::Zero,REDUCTION_TEXTURE_SIZE,REDUCTION_TEXTURE_NAME)
{
	_initMap[L"Reduction"] = std::make_shared<Act>([this]() { changeTextureName(REDUCTION_TEXTURE_SIZE, REDUCTION_TEXTURE_NAME); });
	_initMap[L"Enlarged"]  = std::make_shared<Act>([this]() { changeTextureName(ENLARGED_TEXTURE_SIZE , ENLARGED_TEXTURE_NAME ); });

	_actMap[L"ArmUp"]   = std::make_shared<Act>([this]() { changeTextureAct(ARM_SPAN, ARMUP_TEXTURE_POS_LIST); });
	_actMap[L"ArmDown"] = std::make_shared<Act>([this]() { changeTextureAct(ARM_SPAN, ARMDOWN_TEXTURE_POS_LIST); });
}
