#include "BoxRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(60,60);                    // 拡大版の画像のサイズ
	const String ENLARGED_TEXTURE_NAME = L"BoxRobot(reduction)";  // 拡大版の画像の名前
	const Size   REDUCTION_TEXTURE_SIZE(30, 30);                  // 縮小版の画像のサイズ
	const String REDUCTION_TEXTURE_NAME = L"BoxRobot(reduction)"; // 縮小版の画像の名前

	const size_t             BLINK_SPAN             = 3; // まばたき時の画像を切り替えるフレームの間隔
	const std::vector<Point> BLINK_TEXTURE_POS_LIST      // まばたきの画像のリスト
	{ Point(1,0),Point(2,0),Point(3,0),Point(2,0),Point(1,0),Point(0,0) };

	const size_t SLEEP_SPAN = 30;                   // 睡眠時の画像を切り替えるフレームの間隔
	const std::vector<Point> SLEEP_TEXTURE_POS_LIST // 睡眠の画像のリスト
	{ Point(0,1),Point(1,1),Point(2,1),Point(3,1) };

	const size_t WAKE_SPAN = 6;                    // 起きる時の画像を切り替えるフレームの間隔
	const std::vector<Point> WAKE_TEXTURE_POS_LIST // 起きる画像のリスト
	{ Point(3,0),Point(2,0),Point(1,0),Point(0,0) };
}


Robot::BoxRobotObject::BoxRobotObject(const Point & pos)
	: ChangeTextureObject(pos,Point::Zero,REDUCTION_TEXTURE_SIZE,REDUCTION_TEXTURE_NAME)
{
	_initMap[L"Reduction"] = std::make_shared<Act>([this]() { changeTextureName(REDUCTION_TEXTURE_SIZE, REDUCTION_TEXTURE_NAME); });
	_initMap[L"Enlarged"]  = std::make_shared<Act>([this]() { changeTextureName(ENLARGED_TEXTURE_SIZE , ENLARGED_TEXTURE_NAME ); });
	_initMap[L"Sleep"]     = std::make_shared<Act>([this]() { setTextureUpdating(SLEEP_SPAN,SLEEP_TEXTURE_POS_LIST); });

	_actMap[L"Blink"] = std::make_shared<Act>([this]() {changeTextureAct(BLINK_SPAN, BLINK_TEXTURE_POS_LIST);});
	_actMap[L"Wake"]  = std::make_shared<Act>([this]() {changeTextureAct(WAKE_SPAN , WAKE_TEXTURE_POS_LIST); });
}

