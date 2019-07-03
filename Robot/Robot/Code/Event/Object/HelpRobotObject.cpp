#include "HelpRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(50, 100);                   // �g��ł̉摜�̃T�C�Y
	const String ENLARGED_TEXTURE_NAME = L"HelpRobot(reduction)";  // �g��ł̉摜�̖��O
	const Size   REDUCTION_TEXTURE_SIZE(50, 100);                  // �k���ł̉摜�̃T�C�Y
	const String REDUCTION_TEXTURE_NAME = L"HelpRobot(reduction)"; // �k���ł̉摜�̖��O
}


Robot::HelpRobotObject::HelpRobotObject(const Point & pos)
	: ChangeTextureObject(pos,Point::Zero,REDUCTION_TEXTURE_SIZE,REDUCTION_TEXTURE_NAME)
{
	_initMap[L"Reduction"] = std::make_shared<Act>([this]() { changeTextureName(REDUCTION_TEXTURE_SIZE, REDUCTION_TEXTURE_NAME); });
	_initMap[L"Enlarged"]  = std::make_shared<Act>([this]() { changeTextureName(ENLARGED_TEXTURE_SIZE , ENLARGED_TEXTURE_NAME ); });
}
