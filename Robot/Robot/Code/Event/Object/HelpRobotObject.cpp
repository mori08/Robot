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

	const size_t ACCESS_SPAN = 30;                   // 通信時の画像を切り替えるフレームの間隔
	const std::vector<Point> ACCESS_TEXTURE_POS_LIST // 通信する画像のリスト
	{ Point(4,0),Point(5,0),Point(6,0) };

	const Point BLOOD_POS(3, 0); // 血まみれの画像の番号
}


Robot::HelpRobotObject::HelpRobotObject(const Point & pos)
	: ChangeTextureObject(pos,Point::Zero,REDUCTION_TEXTURE_SIZE,REDUCTION_TEXTURE_NAME)
{
	_initMap[L"Reduction"] = std::make_shared<Act>([this]() { changeTextureName(REDUCTION_TEXTURE_SIZE, REDUCTION_TEXTURE_NAME); });
	_initMap[L"Enlarged"]  = std::make_shared<Act>([this]() { changeTextureName(ENLARGED_TEXTURE_SIZE , ENLARGED_TEXTURE_NAME ); });
	_initMap[L"Blood"]     = std::make_shared<Act>([this]() { setTexturePos(BLOOD_POS); });

	_actMap[L"ArmUp"]   = std::make_shared<Act>([this]() { changeTextureAct(ARM_SPAN, ARMUP_TEXTURE_POS_LIST); });
	_actMap[L"ArmDown"] = std::make_shared<Act>([this]() { changeTextureAct(ARM_SPAN, ARMDOWN_TEXTURE_POS_LIST); });
	_actMap[L"Access"]  = std::make_shared<Act>([this]() { changeTextureAct(ACCESS_SPAN, ACCESS_TEXTURE_POS_LIST); });
}
