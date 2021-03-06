#include "BoxRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(60,60);                    // 拡大版の画像のサイズ
	const String ENLARGED_TEXTURE_NAME = L"BoxRobot(enlarged)";   // 拡大版の画像の名前
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

	const size_t SURPRISED_SPAN = 10;                  // 驚く時の画像を切り替えるフレームの間隔
	const std::vector<Point> SURPRISD_TEXTURE_POS_LIST // 驚く画像のリスト
	{ Point(0,2),Point(1,2),Point(2,2),Point(3,2),Point(3,2),Point(3,2),Point(3,2),Point(3,2),Point(0,0) };

	const size_t ACCESS_SPAN = 8;                    // 通信時の画像を切り替えるフレームの間隔
	const std::vector<Point> ACCESS_TEXTURE_POS_LIST // 通信する画像のリスト
	{ Point(0,3),Point(1,3),Point(2,3),Point(3,3),Point(3,3),Point(0,4),Point(1,4),Point(2,4) };

	const size_t DOT_SPAN = 30;                   // 考える時の画像を切り替えるフレーム数
	const std::vector<Point> DOT_TEXTURE_POS_LIST // 考える画像のリスト
	{ Point(3,4),Point(0,5),Point(1,5),Point(1,5),Point(0,0) };

	const size_t TIRED_SPAN = 60;                    // 疲れの画像を切り替えるフレーム数
	const std::vector<Point> TIRED_TEXTURE_POS_LIST  // 疲れ画像のリスト
	{ Point(2,5),Point(3,5) };

	const size_t ERROR_SPAN = 60;                    // 壊れの画像を切り替えるフレーム数
	const std::vector<Point> ERROR_TEXTURE_POS_LIST  // 壊れの画像のリスト
	{ Point(2,5),Point(3,5),Point(0,6),Point(1,6),Point(2,6),Point(3,6) };

	const Point BROKEN_POS(3, 6); // 壊れた画像の番号
}


Robot::BoxRobotObject::BoxRobotObject(const Point & pos)
	: ChangeTextureObject(pos,Point::Zero,REDUCTION_TEXTURE_SIZE,REDUCTION_TEXTURE_NAME)
{
	_initMap[L"Reduction"] = std::make_shared<Act>([this]() { changeTextureName(REDUCTION_TEXTURE_SIZE, REDUCTION_TEXTURE_NAME); });
	_initMap[L"Enlarged"]  = std::make_shared<Act>([this]() { changeTextureName(ENLARGED_TEXTURE_SIZE , ENLARGED_TEXTURE_NAME ); });
	_initMap[L"Sleep"]     = std::make_shared<Act>([this]() { setTextureUpdating(SLEEP_SPAN, SLEEP_TEXTURE_POS_LIST); });
	_initMap[L"Tired"]     = std::make_shared<Act>([this]() { setTextureUpdating(TIRED_SPAN, TIRED_TEXTURE_POS_LIST); });
	_initMap[L"Error"]     = std::make_shared<Act>([this]() { setTextureUpdating(ERROR_SPAN, ERROR_TEXTURE_POS_LIST); });
	_initMap[L"Broken"]    = std::make_shared<Act>([this]() { setTexturePos(BROKEN_POS); });

	_actMap[L"Blink"]     = std::make_shared<Act>([this]() {changeTextureAct(BLINK_SPAN    , BLINK_TEXTURE_POS_LIST   ); });
	_actMap[L"Wake"]      = std::make_shared<Act>([this]() {changeTextureAct(WAKE_SPAN     , WAKE_TEXTURE_POS_LIST    ); });
	_actMap[L"Surprised"] = std::make_shared<Act>([this]() {changeTextureAct(SURPRISED_SPAN, SURPRISD_TEXTURE_POS_LIST); });
	_actMap[L"Access"]    = std::make_shared<Act>([this]() {changeTextureAct(ACCESS_SPAN   , ACCESS_TEXTURE_POS_LIST  ); });
	_actMap[L"Dot"]       = std::make_shared<Act>([this]() {changeTextureAct(DOT_SPAN      , DOT_TEXTURE_POS_LIST     ); });
}

