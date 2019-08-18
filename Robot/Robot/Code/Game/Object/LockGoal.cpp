#include "LockGoal.h"
#include "../../MyColor.h"


namespace
{
	const int KEY_NUM = 4; // 鍵の数
	const std::vector<Point> KEY_POINT // LockKeyを生成する座標
	{
		Point(0                          , 0),
		Point(Robot::StageData::WIDTH - 1, 0),
		Point(Robot::StageData::WIDTH - 1, Robot::StageData::HEIGHT - 1),
		Point(0                          , Robot::StageData::HEIGHT - 1)
	};

	const double SPEED = 0.1;
	const double MIN_VEC_LENGTH = 0.05;

	const double CLEAR_DISTANCE = 5.0; // クリア判定が行われる距離

	const Size   TEXTURE_SIZE(40, 40); // 画像のサイズ

	const int    CHANGE_TEXTURE_SPAN = 10;  // 画像を変更するフレーム数

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


void Robot::LockGoal::update(GameManager & gameManager)
{
	updateKey();

	Vec2 moveVec = gameManager.getPath(_pos, _goal);
	if (moveVec.length() < MIN_VEC_LENGTH)
	{
		_goal = RandomVec2(StageData::SIZE*StageData::WIDTH, StageData::SIZE*StageData::HEIGHT);
	}
	moveObject(gameManager, SPEED*moveVec);

	if (_lastKeyNum > 0) { return; }

	gameManager.setGoalPos(_pos);

	if (++_frameCount%CHANGE_TEXTURE_SPAN == 0)
	{
		_texturePos.x++;
	}

	if ((_pos - gameManager.getPlayerPos()).length() < CLEAR_DISTANCE)
	{
		gameManager.gameClear();
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
		FontAsset(L"20")(L"鍵が足りない").drawAt(DRAW_TEXT_POS, Palette::MyWhite);
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
		key.update(GameManager::Instance());

		if (!key.checkPlayer(GameManager::Instance())) { continue; }

		--_lastKeyNum;
	}
}
