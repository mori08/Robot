#include "LockGoal.h"
#include "../../MyColor.h"


namespace
{
	const int KEY_NUM = 4; // ���̐�
	const std::vector<Point> KEY_POINT // LockKey�𐶐�������W
	{
		Point(0                          , 0),
		Point(Robot::StageData::WIDTH - 1, 0),
		Point(Robot::StageData::WIDTH - 1, Robot::StageData::HEIGHT - 1),
		Point(0                          , Robot::StageData::HEIGHT - 1)
	};

	const double SPEED = 0.1;
	const double MIN_VEC_LENGTH = 0.05;

	const double CLEAR_DISTANCE = 5.0; // �N���A���肪�s���鋗��

	const Size   TEXTURE_SIZE(40, 40); // �摜�̃T�C�Y

	const int    CHANGE_TEXTURE_SPAN = 10;  // �摜��ύX����t���[����

	const Point  DRAW_TEXT_POS(320, 460);
}


Robot::LockGoal::LockGoal(const Vec2 & pos)
	: GameObject(pos)
	, _frameCount(0)
	, _lastKeyNum(KEY_NUM)
	, _texturePos(0,0)
{
	_goal = pos;

	for (int i = 0; i < KEY_NUM; ++i)
	{
		_keyList.emplace_back(StageData::centerPosOfCell(KEY_POINT[i]));
	}
}


void Robot::LockGoal::update()
{
	updateKey();

	// �����_���ȍ��W�ֈړ�
	Vec2 moveVec = GameManager::Instance().getPath(_pos, _goal);
	if (moveVec.length() < MIN_VEC_LENGTH)
	{
		_goal = RandomVec2(StageData::SIZE*StageData::WIDTH, StageData::SIZE*StageData::HEIGHT);
	}
	moveObject(SPEED*moveVec);

	if (_lastKeyNum > 0) { return; }

	GameManager::Instance().setGoalPos(_pos);

	if (++_frameCount%CHANGE_TEXTURE_SPAN == 0)
	{
		_texturePos.x++;
	}

	if ((_pos - GameManager::Instance().getPlayerPos()).length() < CLEAR_DISTANCE)
	{
		GameManager::Instance().gameClear();
	}
}


void Robot::LockGoal::draw() const
{
	TextureAsset(L"Goal")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);

	for(const auto & key : _keyList)
	{
		key.draw();
	}

	if (_lastKeyNum > 0 && (_pos - GameManager::Instance().getPlayerPos()).length() < CLEAR_DISTANCE)
	{
		FontAsset(L"20")(L"��������Ȃ�").drawAt(DRAW_TEXT_POS, Palette::MyWhite);
	}
}


void Robot::LockGoal::drawLight() const
{
	for (const auto & key : _keyList)
	{
		key.drawLight();
	}
}


void Robot::LockGoal::updateKey()
{
	for (auto & key : _keyList)
	{
		key.update();

		if (!key.checkPlayer()) { continue; }

		--_lastKeyNum;
	}
}
