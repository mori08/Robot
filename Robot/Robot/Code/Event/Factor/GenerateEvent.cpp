#include "GenerateEvent.h"

#include "../Object/TestEventObject.h"
#include "../Object/BoxRobotObject.h"
#include "../Object/HelpRobotObject.h"


namespace
{
	const size_t INFO_SIZE = 4; // �ڍׂ̔z��̃T�C�Y

	const size_t TYPE = 0; // �I�u�W�F�N�g�̎�ނ̃C���f�b�N�X
	const size_t NAME = 1; // �I�u�W�F�N�g�̖��O�̃C���f�b�N�X
	const size_t X    = 2; // X���W�̃C���f�b�N�X
	const size_t Y    = 3; // Y���W�̃C���f�b�N�X

	const int RADIX = 10; // 10�i��
}


Robot::GenerateEvent::FuncMap Robot::GenerateEvent::generateObjMap;


bool Robot::GenerateEvent::load(const Info & info, const EventManager &)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	_type = info[TYPE];
	_name = info[NAME];
	if (generateObjMap.find(_type) == generateObjMap.end())
	{
		printError(L"�I�u�W�F�N�g�̌^[" + _type + L"]�͑��݂��܂���");
		return false;
	}

	Optional<int> optX = FromStringOpt<int>(info[X], RADIX);
	Optional<int> optY = FromStringOpt<int>(info[Y], RADIX);
	if (!optX || !optY)
	{
		printError(L"���l�ł͂Ȃ��l���w�肳��܂���");
		printError(L"x : " + info[X] + L" , y : " + info[Y]);
		return false;
	}
	_pos.x = *optX;
	_pos.y = *optY;

	return _isSuccess = true;
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
	makeGenerateFunc<BoxRobotObject> (L"BoxRobot");
	makeGenerateFunc<HelpRobotObject>(L"HelpRobot");
}
