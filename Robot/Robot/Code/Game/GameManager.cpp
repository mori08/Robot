#include "GameManager.h"
#include "Object\TestGameObject.h"
#include "Object\GamePlayer.h"


void Robot::GameManager::load(const String & gameDataFileName)
{
	_objList.clear();
	_stageData.clear();

	CSVReader gameData(gameDataFileName);
	if (!gameData.isOpened())
	{
		printError(L"Error > GameData��ǂݍ��߂܂���ł����B : " + gameDataFileName);
		return;
	}

	// �X�e�[�W�f�[�^�̐ݒ�
	if (gameData.rows < StageData::HEIGHT)
	{
		printError(L"Error > GameData���X�e�[�W�f�[�^�̍s��������܂���B");
		printError(L"rows : " + ToString(gameData.rows));
		return;
	}
	for (int y = 0; y < StageData::HEIGHT; ++y)
	{
		if (gameData.columns(y) < StageData::WIDTH)
		{
			printError(L"Error > GameData���X�e�[�W�f�[�^�̗񐔂�����܂���B");
			printError(L"columns : " + ToString(gameData.columns(y)));
			return;
		}
		for (int x = 0; x < StageData::WIDTH; ++x)
		{
			if (gameData.get<int>(y, x) == 1)
			{
				_stageData.setWall(x, y);
			}
		}
	}

	// �o�H�T��
	_stageData.searchPath();

	_objList.emplace_back(std::make_unique<GamePlayer>(Vec2(200, 200)));

	_objList.emplace_back(std::make_unique<TestGameObject>());

	// ���̏����ʒu�̐ݒ�
	_light.setPos(Window::Center());
}


void Robot::GameManager::update()
{
	_light.update();

	for (auto && obj : _objList)
	{
		obj->update(*this);
	}
}


void Robot::GameManager::draw() const
{
#ifdef _DEBUG
	if (Input::Key0.pressed)
	{
		// ���𔖂��`��
		Window::ClientRect().draw(Color(Palette::MyWhite, 128));
	}
#endif // _DEBUG

	_light.draw();

	for (const auto & obj : _objList)
	{
		obj->draw();
	}

	_stageData.draw();
}
