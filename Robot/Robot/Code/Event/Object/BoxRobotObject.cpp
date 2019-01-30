#include "BoxRobotObject.h"


namespace
{
	const Size   ENLARGED_TEXTURE_SIZE(60,60);                    // �g��ł̉摜�̃T�C�Y
	const String ENLARGED_TEXTURE_NAME = L"BoxRobot(reduction)";  // �g��ł̉摜�̖��O
	const Size   REDUCTION_TEXTURE_SIZE(30, 30);                  // �k���ł̉摜�̃T�C�Y
	const String REDUCTION_TEXTURE_NAME = L"BoxRobot(reduction)"; // �k���ł̉摜�̖��O

	const int BLINK_SPAN = 4; // �܂΂������̉摜��؂�ւ���t���[���Ԋu
	const std::vector<Point> BLINK_TEXTURE_POS_LIST{ Point(1,0),Point(2,0),Point(3,0),Point(0,0) };
}


Robot::BoxRobotObject::BoxRobotObject(const Point & pos)
	: EventObject(pos)
	, _textureSize(REDUCTION_TEXTURE_SIZE)
	, _textureName(REDUCTION_TEXTURE_NAME)
	, _texturePos(Point::Zero)
{
	_initMap[L"Reduction"] = std::make_shared<Act>([this]() { reduction(); });
	_initMap[L"Enlarged"]  = std::make_shared<Act>([this]() { enlarged(); });

	_actMap[L"Blink"] = std::make_shared<Act>([this]() {changeTextureAct(BLINK_SPAN,BLINK_TEXTURE_POS_LIST);});
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


void Robot::BoxRobotObject::changeTextureAct(int span, const std::vector<Point>& texturePosList)
{
	int nextPosId = _actFrameCount / span;

	if (nextPosId >= (int)texturePosList.size()) 
	{
		finishAct();
		return; 
	}

	_texturePos = texturePosList[nextPosId];
}



