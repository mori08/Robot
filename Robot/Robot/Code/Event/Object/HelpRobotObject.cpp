#include "HelpRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(50, 100);                   // �g��ł̉摜�̃T�C�Y
	const String ENLARGED_TEXTURE_NAME = L"HelpRobot(reduction)";  // �g��ł̉摜�̖��O
	const Size   REDUCTION_TEXTURE_SIZE(50, 100);                  // �k���ł̉摜�̃T�C�Y
	const String REDUCTION_TEXTURE_NAME = L"HelpRobot(reduction)"; // �k���ł̉摜�̖��O

	const size_t             ARM_SPAN = 5;            // �r�𓮂��������̉摜��؂�ւ���t���[���̊Ԋu
	const std::vector<Point> ARMUP_TEXTURE_POS_LIST   // �r���オ�铮���̉摜�̃��X�g
	{ Point(0,0),Point(1,0),Point(2,0) };
	const std::vector<Point> ARMDOWN_TEXTURE_POS_LIST // �r�������铮���̉摜�̃��X�g
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
