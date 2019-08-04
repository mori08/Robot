#include "EventManager.h"

#include "Factor\StartEvent.h"
#include "Factor\GenerateEvent.h"
#include "Factor\BackgroundEvent.h"
#include "Factor\WaitEvent.h"
#include "Factor\MoveEvent.h"
#include "Factor\ActEvent.h"
#include "Factor\ShakeEvent.h"
#include "Factor\TextEvent.h"
#include "Factor\SceneEvent.h"
#include "Factor\ShadowEvent.h"
#include "Factor\InitEvent.h"
#include "Factor\DarkEvent.h"
#include "Factor\HideEvent.h"


namespace
{
	const int EVENT_NAME_COLUMN = 0;           // CSV�t�@�C�����̃C�x���g�̖��O���L�q�����
	const int EVENT_INFO_COLUMN = 1;           // CSV�t�@�C�����̃C�x���g�̏ڍׂ��ŏ��ɋL�q�����
	const String EVENT_INFO_END = L"#";        // CSV�t�@�C�����ŃC�x���g�̏ڍׂ̍Ō�Ɏg��������
	const String RUN_EVENT_KEY  = L"Run";      // CSV�t�@�C�����œo�^�ς݂̃C�x���g��S�Ď��s���閽��
	const String FUNC_EVENT_KEY = L"Function"; // CSV�t�@�C�����ŕ�CSV�t�@�C���̃C�x���g��ǂݍ��ޖ���

	const Size EVENT_SIZE(640, 320); // �e�L�X�g�{�b�N�X�������C�x���g�̃T�C�Y

	const RoundRect SHADOW_SHAPE(50, 50, 540, 220, 100); // �e�̌`

	const int SHADOW_BLUR = 100; // �e�̂ڂ����̑傫��

	const int SPREAD_BASE = 80; // �e�̍L������̊
	const int SPREAD_RAND = 10; // �e�̍L������̂���̕p�x

	const int COLOR_BASE  = 245; // �e�̐F�̊
	const int COLOR_WIDTH = 3;   // �e�̐F�̂���̑傫��
	const int COLOR_RAND  = 120; // �e�̐F�̂���̕p�x

	const int LINE_RAND  = 30; // �e�̐��������p�x
	const int LINE_WIDTH = 1;  // �e�̐��̕�

	const int DARK_ALPHA_CHANGE_SPEED = 5; // �Ó]�̕s�����x��ύX���鑬��
}


Robot::EventManager::EventManager()
	: _frameCount(0)
	, _shakeSize(0)
	, _shakeFrameCount(0)
	, _spanShakeFrameCount(0)
{

}


void Robot::EventManager::setAllEvent()
{
	setEvent<GenerateEvent>  (L"Generate");
	setEvent<BackgroundEvent>(L"Background");
	setEvent<WaitEvent>      (L"Wait");
	setEvent<MoveEvent>      (L"Move");
	setEvent<ActEvent>       (L"Act");
	setEvent<ShakeEvent>     (L"Shake");
	setEvent<TextEvent>      (L"Text");
	setEvent<SceneEvent>     (L"Scene");
	setEvent<ShadowEvent>    (L"Shadow");
	setEvent<InitEvent>      (L"Init");
	setEvent<DarkEvent>      (L"Dark");
	setEvent<HideEvent>      (L"Hide");
}


void Robot::EventManager::init()
{
	// �o�߃t���[���� 0 �ɖ߂��܂�
	resetFrameCount();

	// �C�x���g�I�u�W�F�N�g��S�č폜���܂�
	_objectList.clear();

	// �C�x���g�̃L���[����ɂ��܂�
	while (!_eventQueue.empty()) { _eventQueue.pop(); }

	// ��̃C�x���g���L���[�ɓ���܂�
	_eventQueue.push(std::make_unique<StartEvent>());

	// �e�L�X�g�{�b�N�X�����������܂�
	_textBox.reset();

	// �V�[���J�ڂ�s���ɂ��܂�
	_isChangeAbleScene = false;

	// �J�ڐ���^�C�g���ɂ��܂�
	_sceneName = { L"TitleScene",L"" };

	// �e����菜���܂�
	_shadow = false;

	// �Ó]����菜���܂�
	_darkAlpha = { 0,0 };
}


bool Robot::EventManager::translateEventData(const CSVReader & eventFile)
{
	for (int loadingRow = 0; loadingRow < eventFile.rows; ++loadingRow)
	{
		// �C�x���g�̖��O�̎擾
		String eventName = eventFile.get<String>(loadingRow, EVENT_NAME_COLUMN);

		// ���݃L���[�ɂ���S�C�x���g�����s����
		if (eventName == RUN_EVENT_KEY) 
		{
			runAllEvent();
			continue;
		}
		
		// ��CSV�t�@�C����ǂݍ���
		if (eventName == FUNC_EVENT_KEY)
		{
			String funcFileName = eventFile.get<String>(loadingRow, EVENT_INFO_COLUMN);
			CSVReader reader(L"Asset/Data/Event/Function/" + funcFileName + L".csv");
			if (!reader.isOpened())
			{
				printError(L"�C�x���g�֐��t�@�C��[" + FileSystem::BaseName(reader.path()) + L"] �͑��݂��܂���");
				printError(L"[" + eventFile.path() + L"] " + ToString(loadingRow + 1) + L"�s��");
			}
			if (!translateEventData(reader))
			{
				return false;
			}
			continue;
		}

		// �C�x���g�����݂��邩���m�F
		if (_makeEventMap.find(eventName) == _makeEventMap.end())
		{
			printError(L"�C�x���g[" + eventName + L"] �͑��݂��܂���");
			printError(L"[" + FileSystem::BaseName(eventFile.path()) + L"] " + ToString(loadingRow + 1) + L"�s��");
			return false;
		}

		// �C�x���g�̏ڍׂ̍쐬
		EventInfo eventInfo;
		for (int column = EVENT_INFO_COLUMN; ; ++column)
		{
			// �I��������������Ȃ��Ƃ��G���[
			if (column >= eventFile.columns(loadingRow))
			{
				printError(L"�I������[" + EVENT_INFO_END + L"]������܂���");
				printError(L"[" + FileSystem::BaseName(eventFile.path()) + L"] " + ToString(loadingRow + 1) + L"�s��");
				return false;
			}

			// �I�����������������Ƃ����[�v�𔲂���
			if (eventFile.get<String>(loadingRow, column) == EVENT_INFO_END) { break; }

			// �ڍׂɒǉ�����
			eventInfo.emplace_back(eventFile.get<String>(loadingRow, column));
		}

		// �C�x���g�̃|�C���^�𐶐�����
		EventPtr eventPtr = _makeEventMap[eventName]();

		// �C�x���g�̏ڍׂ�ǂݍ��݂܂�
		if (!eventPtr->load(eventInfo, *this))
		{
			printError(L"[" + FileSystem::BaseName(eventFile.path()) + L"] " + ToString(loadingRow + 1) + L"�s��");
			return false;
		}

		// �L���[�ɃC�x���g��ǉ�����
		_eventQueue.push(std::move(eventPtr));
	}

	return true;
}


void Robot::EventManager::runAllEvent()
{
	while (!_eventQueue.empty())
	{
		_eventQueue.front()->checkAndPerform(*this);
		_eventQueue.pop();
	}

	_eventQueue.push(std::make_unique<StartEvent>());
}


const Vec2 Robot::EventManager::getShakePos() const
{
	if (_shakeFrameCount >= _spanShakeFrameCount)
	{
		return Vec2::Zero;
	}

	return Vec2(Random(-_shakeSize, _shakeSize), Random(-_shakeSize, _shakeSize));
}


void Robot::EventManager::drawShadow() const
{
	if (!_shadow)
	{
		Window::ClientRect().draw(Palette::MyWhite);
		return;
	}

	SHADOW_SHAPE.drawShadow(
		Vec2::Zero,
		SHADOW_BLUR,
		SPREAD_BASE + Random(SPREAD_RAND) / SPREAD_RAND,
		Color(COLOR_BASE - COLOR_WIDTH*Random(COLOR_BASE) / COLOR_BASE)
		);

	if (Random(LINE_RAND) == 0)
	{
		Rect(0, Random(EVENT_SIZE.y), EVENT_SIZE.x, LINE_WIDTH).draw(Palette::MyBlack);
	}
}


void Robot::EventManager::load(const String & eventFileName)
{
	init();

	CSVReader reader(eventFileName);
	if (!reader.isOpened())
	{
		printError(L"Error > Event��ǂݍ��߂܂���ł����B : " + eventFileName);
		return;
	}

	_isSuccess = translateEventData(reader);
}


void Robot::EventManager::update()
{
	if (!_isSuccess) { return; }

	++_frameCount;
	++_shakeFrameCount;

	// �L���[�̒��ɃC�x���g��1�����Ȃ�X�L�b�v
	if (_eventQueue.size() > 1 && _eventQueue.front()->isCompleted(*this))
	{
		_eventQueue.pop();
		_eventQueue.front()->checkAndPerform(*this);
	}

	updateEventObject();

	changeDarkAlpha();

	_textBox.update();
}


void Robot::EventManager::updateEventObject()
{
	for (auto & object : _objectList)
	{
		object.second->update();
	}
}


void Robot::EventManager::draw() const
{
	if (!_isSuccess) { return; }

	Vec2 s = getShakePos();

	drawShadow();

	TextureAsset(_backgroundName).draw(s);

	for (const auto & object : _objectList)
	{
		object.second->draw(s);
	}

	Rect(Point::Zero, EVENT_SIZE).draw(Color(Palette::MyBlack, _darkAlpha.first));

	_textBox.draw();
}


bool Robot::EventManager::isChangeAbleScene(String & sceneName, String & sceneInfo) const
{
	if (!_isSuccess)
	{
		sceneName = L"TitleScene";
		return true;
	}

	if (_isChangeAbleScene)
	{
		sceneName = _sceneName.first;
		sceneInfo = _sceneName.second;
	}

	return _isChangeAbleScene;
}


Optional<Robot::EventManager::ObjectPtr> Robot::EventManager::getObjectOpt(const String & name)
{
	if (_objectList.find(name) == _objectList.end())
	{
		return none;
	}
	
	return _objectList[name];
}


bool Robot::EventManager::isWaitingObject(const String & name) const
{
	if (_objectList.find(name) == _objectList.end())
	{
		return true;
	}

	return _objectList.find(name)->second->completeMoveAndAct();
}

void Robot::EventManager::setShake(double size, int span)
{
	if (size < 0 || span < 0)
	{
#ifdef _DEBUG
		Println(L"Error > setShake�֐��ŕs�K�؂Ȓl���w�肳��܂����B");
		Println(L"[size : ", size, L"][span : ", span, L"]");
#endif // _DEBUG
		return;
	}

	_shakeSize           = size;
	_shakeFrameCount     = 0;
	_spanShakeFrameCount = span;
}


void Robot::EventManager::setSceneName(const String & sceneName, const String & sceneInfo)
{
	_isChangeAbleScene = true;
	_sceneName = { sceneName,sceneInfo };
}


void Robot::EventManager::changeDarkAlpha()
{
	if (_darkAlpha.first > _darkAlpha.second)
	{
		_darkAlpha.first -= DARK_ALPHA_CHANGE_SPEED;
		return;
	}

	if (_darkAlpha.first < _darkAlpha.second)
	{
		_darkAlpha.first += DARK_ALPHA_CHANGE_SPEED;
		return;
	}
}


