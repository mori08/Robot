#include "BoxRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(60,60);                    // �g��ł̉摜�̃T�C�Y
	const String ENLARGED_TEXTURE_NAME = L"BoxRobot(reduction)";  // �g��ł̉摜�̖��O
	const Size   REDUCTION_TEXTURE_SIZE(30, 30);                  // �k���ł̉摜�̃T�C�Y
	const String REDUCTION_TEXTURE_NAME = L"BoxRobot(reduction)"; // �k���ł̉摜�̖��O

	const size_t             BLINK_SPAN             = 3; // �܂΂������̉摜��؂�ւ���t���[���̊Ԋu
	const std::vector<Point> BLINK_TEXTURE_POS_LIST      // �܂΂����̉摜�̃��X�g
	{ Point(1,0),Point(2,0),Point(3,0),Point(2,0),Point(1,0),Point(0,0) };

	const size_t SLEEP_SPAN = 30;                   // �������̉摜��؂�ւ���t���[���̊Ԋu
	const std::vector<Point> SLEEP_TEXTURE_POS_LIST // �����̉摜�̃��X�g
	{ Point(0,1),Point(1,1),Point(2,1),Point(3,1) };

	const size_t WAKE_SPAN = 6;                    // �N���鎞�̉摜��؂�ւ���t���[���̊Ԋu
	const std::vector<Point> WAKE_TEXTURE_POS_LIST // �N����摜�̃��X�g
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

