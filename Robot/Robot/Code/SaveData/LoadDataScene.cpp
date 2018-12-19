#include"LoadDataScene.h"


namespace
{
	const int   LOADING_FRAME = 4;      // ��R�}�ɂ�����t���[����
	const int   LOADING_NUM   = 6;      // �摜�̐�
	const Size  LOADING_SIZE(40 , 30);  // �摜�̃T�C�Y
	const Point LOADING_POS (430, 420); // �`�悷����W

	const Point LOADING_TEXT_POS = LOADING_POS + Point(60, 0); // �uLoading�v��\��������W
}


Robot::LoadDataScene::LoadDataScene()
{
	_isLoading  = true;
	_frameCount = 0;
	_loadThread = std::thread([this]() {_loadResult = SaveDataManager::Instance().load(); });
}


Robot::LoadDataScene::~LoadDataScene()
{
	if (_isLoading)
	{
		_loadThread.join();
	}
}


void Robot::LoadDataScene::init()
{
	
}


void Robot::LoadDataScene::update()
{
	++_frameCount;

	if (_isLoading && _loadThread.joinable())
	{
		_loadThread.join();
		_isLoading = false;

		switch(_loadResult)
		{
		case SaveDataManager::LoadResult::NEW_GAME:
		case SaveDataManager::LoadResult::CONTINUE:
		case SaveDataManager::LoadResult::ERROR:
			changeScene(L"TitleScene");
			break;
		}
		
	}
}


void Robot::LoadDataScene::updateFadeIn(double)
{
	++_frameCount;
}


void Robot::LoadDataScene::updateFadeOut(double)
{
	++_frameCount;
}


void Robot::LoadDataScene::draw() const
{
	const int i = (_frameCount % (LOADING_FRAME*LOADING_NUM)) / LOADING_FRAME; // �\������摜�̔ԍ����v�Z
	
	TextureAsset(L"Loading")(i*LOADING_SIZE.x, 0, LOADING_SIZE).draw(LOADING_POS);

	FontAsset(L"20")(L"Loading" + String(L"......").substr(0, i)).draw(Point(LOADING_TEXT_POS));
}


void Robot::LoadDataScene::drawFadeIn(double) const
{
	draw();
}


void Robot::LoadDataScene::drawFadeOut(double) const
{
	draw();
}
