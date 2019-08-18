#pragma once

#include<queue>

#include"Object/EventObject.h"

#include"Factor/EventBase.h"

#include"TextBox.h"

#include"../MyColor.h"

namespace Robot
{
	/*
	EventManager�N���X
	CSV�t�@�C������Event��ǂݍ���
	EventObject�̊Ǘ�
	�w�i����ʁC���o�̐ݒ�
	*/
	class EventManager
	{
	private:

		using ObjectPtr  = std::shared_ptr<EventObject>;
		using ObjectList = std::map<String, ObjectPtr>;

		using EventPtr      = std::unique_ptr<EventBase>;
		using EventInfo     = std::vector<String>;
		using MakeEventFunc = std::function<EventPtr()>;
		using MakeEventMap  = std::unordered_map<String, MakeEventFunc>;

		using EventQueue = std::queue<EventPtr>;

		using SceneName = std::pair<String, String>;

		using DarkAlpha = std::pair<int, int>;

	private:

		String       _name;                // �Ǘ����Ă���C�x���g�̖��O

		bool         _isSuccess;           // ���[�h���������Ă��邩

		ObjectList   _objectList;          // EventOject�̃��X�g

		EventQueue   _eventQueue;          // EventBase�̔h�������o���L���[

		MakeEventMap _makeEventMap;        // �C�x���g�𐶐�����֐��̘A�z�z��

		String       _backgroundName;      // �w�i�摜�̖��O

		int          _frameCount;          // �o�߃t���[����

		double       _shakeSize;           // ��ʂ̗h��̑傫��

		int          _shakeFrameCount;     // ��ʂ̗h��ɂ��Ă̌o�߃t���[����

		int          _spanShakeFrameCount; // ��ʂ�h�炷����

		TextBox      _textBox;             // �e�L�X�g�{�b�N�X

		bool         _isChangeAbleScene;   // �V�[���J�ډ\��

		SceneName    _sceneName;           // { �V�[����, �J�ڐ�̕⑫ }

		DarkAlpha    _darkAlpha;           // { �Ó]�̂Ƃ��̕s�����x,�ړI�n }

		std::function<void()> _whiteDrawFunc; // �w�i�̔���`�悷��֐�

	private:

		EventManager();

		EventManager(const EventManager&)            = default;
		EventManager& operator=(const EventManager&) = default;
		EventManager(EventManager&&)                 = default;
		EventManager& operator=(EventManager&&)      = default;

	public:

		/// <summary>
		/// �V���O���g���Ƃ��ĊǗ����Ă���EventManager�̃C���X�^���X���擾���܂��B
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static EventManager & Instance()
		{
			static EventManager eventManager;
			return eventManager;
		}

		/// <summary>
		/// �S�ẴC�x���g���}�b�v�ɓo�^���܂��B
		/// </summary>
		void setAllEvent();

	private:

		/// <summary>
		/// ������
		/// </summary>
		void init();

		/// <summary>
		/// CSV�f�[�^���C�x���g�ɕϊ����܂��B
		/// </summary>
		/// <param name="eventFileName"> csv�t�@�C���̖��O </param>
		/// <returns> �ϊ��ɐ��������Ƃ� true , �����łȂ��Ƃ� false </returns> 
		bool translateEventData(const CSVReader & eventFile);

		/// <summary>
		/// �P�̃C�x���g���}�b�v�ɓo�^���܂��B
		/// </summary>
		/// <param name="name"> �C�x���g�� </param>
		template<typename eventType>
		void setEvent(const String & name)
		{
			_makeEventMap[name] = MakeEventFunc
			(
				[]()
				{
					return std::move(std::make_unique<eventType>());
				}
			);
		}

		/// <summary>
		/// Event�̃t�@�C����ǂݍ��ݒ���_eventQueue���̑SEvent�����s���܂��B
		/// </summary>
		/// <remarks>
		/// �������p�ɍs���܂��B
		/// isCompleted�֐��ł̔���҂��͍s���܂���
		/// </remarks>
		void runAllEvent();

		/// <summary>
		/// �U���̂�����擾���܂��B
		/// </summary>
		/// <returns> ���炷���W </returns>
		const Vec2 getShakePos() const;

		/// <summary>
		/// �e��`�悵�܂��B
		/// </summary>
		void drawShadow() const;

		/// <summary>
		/// �m�C�Y��`�悵�܂��B
		/// </summary>
		void drawNoise() const;

	public: // EventScene�Ŏg�p����֐�

		/// <summary>
		/// �C�x���g���L�q����csv�t�@�C����ǂݍ���
		/// </summary>
		/// <param name="eventFileName"> csv�t�@�C���̖��O </param>
		void load(const String & eventFileName);

		/// <summary>
		/// �C�x���g�̖��O��ݒ肵�܂��B
		/// </summary>
		/// <param name="name"> �C�x���g�� </param>
		void setName(const String & name)
		{
			_name = name;
		}

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �C�x���g�I�u�W�F�N�g�̍X�V
		/// </summary>
		void updateEventObject();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// �V�[���J�ڐ�������āA�V�[���J�ڂ��\�������܂��B
		/// </summary>
		/// <param name="sceneName"> �V�[���̑J�ڐ� </param>
		/// <param name="sceneInfo"> �J�ڐ�ł̕⑫��� </param>
		/// <returns> �J�ډ\�ȂƂ� true , �����łȂ��Ƃ� false </returns>
		bool isChangeAbleScene(String & sceneName, String & sceneInfo) const;

	public: // EventBase�̔h���N���X�Ŏg�p����֐�

		/// <summary>
		/// EventObject��ǉ����܂��B
		/// </summary>
		/// <param name="name"> ���O </param>
		/// <param name="object"> �I�u�W�F�N�g </param>
		void generateObject(const String & name ,const std::shared_ptr<EventObject> & object)
		{
			_objectList[name] = object;
		}

		/// <summary>
		/// �w�i��ݒ肵�܂��B
		/// </summary>
		/// <param name="name"> �w�i�摜�̖��O </param>
		void setBackground(const String & name)
		{
			_backgroundName = name;
		}

		/// <summary>
		/// �o�߃t���[�������擾���܂��B
		/// </summary>
		int getFrameCount() const
		{
			return _frameCount;
		}

		/// <summary>
		/// �o�߃t���[������0�ɂ��܂��B
		/// </summary>
		void resetFrameCount()
		{
			_frameCount = 0;
		}

		/// <summary>
		/// �I�u�W�F�N�g�����݂��邩�����܂��B
		/// </summary>
		/// <param name="name"> �I�u�W�F�N�g�̖��O </param>
		/// <returns> ���݂���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isExistedObject(const String & name) const
		{
			return _objectList.find(name) != _objectList.end();
		}

		/// <summary>
		/// ����I�u�W�F�N�g�̉��o�����݂��邩�����܂��B
		/// </summary>
		/// <param name=""objectName> �I�u�W�F�N�g�̖��O </param>
		/// <param name="actName"> ���o�̖��O </param>
		/// <returns> ���݂���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isExistedAct(const String & objectName, const String & actName) const
		{
			return isExistedObject(objectName) && _objectList.find(objectName)->second->isExistedAct(actName);
		}

		/// <summary>
		/// ����I�u�W�F�N�g�̏������֐������݂��邩�����܂��B
		/// </summary>
		/// <param name=""objectName> �I�u�W�F�N�g�̖��O </param>
		/// <param name="initName"> �������֐��̖��O </param>
		/// <returns> ���݂���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isExistedInit(const String & objectName, const String & initName) const
		{
			return isExistedObject(objectName) && _objectList.find(objectName)->second->isExistedInit(initName);
		}

		/// <summary>
		/// �I�u�W�F�N�g�̃|�C���^���擾���܂��B
		/// </summary>
		/// <param name="name"> �I�u�W�F�N�g�̖��O </param>
		/// <returns> ���O�ɑΉ�����I�u�W�F�N�g�����݂���Ƃ����̃|�C���^ , ���Ȃ��Ƃ� none </returns>
		Optional<ObjectPtr> getObjectOpt(const String & name);

		/// <summary>
		/// �I�u�W�F�N�g���҂���Ԃ������܂��B
		/// </summary>
		/// <param name="name"> �I�u�W�F�N�g�̖��O </param>
		bool isWaitingObject(const String & name) const;

		/// <summary>
		/// ��ʂ̗h���ݒ肵�܂��B
		/// </summary>
		/// <param name="size"> �h��̑傫�� </param>
		/// <param name="span"> �h�炷���� </param>
		void setShake(double size, int span);

		/// <summary>
		/// ��ʂ̗h�ꂪ�I�����Ă��邩�����܂��B
		/// </summary>
		/// <returns> �I�����Ă���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isCompleteShaking() const
		{
			return _shakeFrameCount > _spanShakeFrameCount;
		}

		/// <summary>
		/// �e�L�X�g�{�b�N�X��ݒ肵�܂��B
		/// </summary>
		/// <param name="speakerName"> �b����̖��O </param>
		/// <param name="iconName"> �A�C�R���̖��O </param>
		/// <param name="text"> �e�L�X�g </param>
		/// <param name="textSpeed"> �e�L�X�g��\�����鑬�� </param>
		void setTextBox(const String & speakerName, const String & iconName, const String & text, int textSpeed)
		{
			_textBox.set(speakerName, iconName, text, textSpeed);
		}

		/// <summary>
		/// �e�L�X�g�{�b�N�X���ݒ�\�������܂��B
		/// </summary>
		/// <returns> �\�ȂƂ� true , �����łȂ��Ƃ� false </returns>
		bool isReadyTextBox() const
		{
			return _textBox.isReady();
		}

		/// <summary>
		/// �V�[���̑J�ڐ��ݒ肵�܂��B
		/// </summary>
		/// <param name="sceneName"> �V�[���̑J�ڐ� </param>
		/// <param name="sceneInfo"> �J�ڐ�̕⑫��� </param>
		void setSceneName(const String & sceneName, const String & sceneInfo);

		/// <summary>
		/// �C�x���g��ǂݍ��݂Ȃ����܂��B
		/// </summary>
		void reload();

		/// <summary>
		/// �e��ݒ肵�܂��B
		/// </summary>
		/// <param name="shadow"> true �̂Ƃ��e��t�^ </param>
		void setShadow(bool shadow)
		{
			_whiteDrawFunc = shadow
				? std::function<void()>([this]() { drawShadow(); })
				: std::function<void()>([this]() { Window::ClientRect().draw(Palette::MyWhite); });
		}

		/// <summary>
		/// �m�C�Y��ݒ肵�܂��B
		/// </summary>
		/// <param name="noise"> true �̂Ƃ��m�C�Y��t�^ </param>
		void setNoise(bool noise)
		{
			_whiteDrawFunc = noise
				? std::function<void()>([this]() { drawNoise(); })
				: std::function<void()>([this]() { Window::ClientRect().draw(Palette::MyWhite); });
		}

		/// <summary>
		/// �Ó]�̕s�����x��ύX���܂��B
		/// </summary>
		void changeDarkAlpha();

		/// <summary>
		/// �Ó]�̕s�����x��ύX�����܂��B
		/// </summary>
		/// <param name="alpha"> �ݒ肵�����s�����x </param>
		void setDarkAlpha(int alpha)
		{
			_darkAlpha.second = alpha;
		}

		/// <summary>
		/// �Ó]�̕s�����x���ύX���I���Ă��邩�Ԃ��܂��B
		/// </summary>
		/// <returns> �ύX���I������Ă���Ȃ� true, �����łȂ��Ȃ� false </returns>
		bool completeChangingDarkAlpha() const
		{
			return _darkAlpha.first == _darkAlpha.second;
		}

	};

}