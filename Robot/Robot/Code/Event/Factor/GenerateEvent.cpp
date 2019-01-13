#include "GenerateEvent.h"

#include "../Object/TestEventObject.h"


namespace
{
	const size_t ARG_SIZE = 4; // �R���X�g���N�^�ň��������̃T�C�Y

	const size_t TYPE = 0; // �I�u�W�F�N�g�̎�ނ̃C���f�b�N�X
	const size_t NAME = 1; // �I�u�W�F�N�g�̖��O�̃C���f�b�N�X
	const size_t X    = 2; // X���W�̃C���f�b�N�X
	const size_t Y    = 3; // Y���W�̃C���f�b�N�X
}


Robot::GenerateEvent::FuncMap Robot::GenerateEvent::generateObjMap;


Robot::GenerateEvent::GenerateEvent(const std::vector<String> & arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEvent�ň����̃T�C�Y������Ă��܂�");
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	_type = arg[TYPE];
	_name = arg[NAME];

	if (generateObjMap.find(_type) == generateObjMap.end()) 
	{
#ifdef _DEBUG
		Println(L"Error > �o�^����Ă��Ȃ�EventObject���ł��B", _type);
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	Optional<int> optX = FromStringOpt<int>(arg[X], 10);
	Optional<int> optY = FromStringOpt<int>(arg[Y], 10);

	if (!optX || !optY)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEvent�Ő��l�łȂ����W���w�肳��܂����B");
		Println(L"[x : ", arg[X], L"] [y : ", arg[Y], L"]");
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	_pos.x = *optX;
	_pos.y = *optY;
}


void Robot::GenerateEvent::perform(EventManager & eventManager) const
{
	eventManager.generateObject(_name, generateObjMap[_type](_pos));
}


bool Robot::GenerateEvent::isCompleted(const EventManager &) const
{
	return true;
}


void Robot::GenerateEvent::setObjectMap()
{
	makeGenerateFunc<TestEventObject>(L"TestEventObject");
}
