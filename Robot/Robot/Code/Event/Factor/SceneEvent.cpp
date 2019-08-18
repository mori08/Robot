#include "SceneEvent.h"
#include "../../MyLibrary.h"


namespace
{
	const size_t INFO_SIZE = 2; // �ڍׂ̔z��̃T�C�Y

	const size_t SCENE_NAME = 0; // �V�[�����̃C���f�b�N�X
	const size_t SCENE_INFO = 1; // �J�ڐ�̃V�[���ŗp����⑫���̃C���f�b�N�X
}


bool Robot::SceneEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	_sceneName = info[SCENE_NAME];
	_sceneInfo = info[SCENE_INFO];

	return _isSuccess = true;
}


void Robot::SceneEvent::perform() const
{
	EventManager::Instance().setSceneName(_sceneName, _sceneInfo);
}

bool Robot::SceneEvent::isCompleted() const
{
	return true;
}
