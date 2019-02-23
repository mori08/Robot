#pragma once


#include "StageData.h"
#include "Object\GameObject.h"
#include "State\GameState.h"
#include "GameLight.h"


namespace
{
	// �I�u�W�F�N�g�̃|�C���^
	using ObjPtr = std::unique_ptr<Robot::GameObject>;

	// �I�u�W�F�N�g�̃��X�g
	using ObjList = std::vector<ObjPtr>;

	// �I�u�W�F�N�g�𐶐�����֐�
	using GenerateFunc = std::function<ObjPtr(const Vec2 & pos)>;

	// ��Ԃ̃|�C���^
	using StatePtr = std::unique_ptr<Robot::GameState>;
}


namespace Robot
{
	/*
	GameManager�N���X
	CSV�t�@�C������Q�[���f�[�^��ǂݍ���
	GameObject�EGameLight�̊Ǘ�
	��Q���̕`��
	*/
	class GameManager
	{
	private:

		// �I�u�W�F�N�g�𐶐�����֐��̃}�b�v
		using FuncMap = std::unordered_map<String, GenerateFunc>;

	private:

		static FuncMap genarateEnemyMap; // �I�u�W�F�N�g�𐶐�����֐��̃}�b�v

	private:

		String     _stageName; // �X�e�[�W��

		StatePtr   _gameState; // ���

		StageData  _stageData; // �X�e�[�W�f�[�^

		ObjList    _objList;   // �I�u�W�F�N�g�̃��X�g

		GameLight  _light;     // ��

		Vec2       _playerPos; // �v���C���[�̍��W

		Vec2       _goalPos;   // �S�[���̍��W

		bool       _isChangeAbleScene; // �V�[���J�ډ\��

		String     _sceneName; // �V�[����

		String     _sceneInfo; // �V�[���̑J�ڐ�̕⑫

	private:

		GameManager()
		{

		}

		GameManager(const GameManager &)             = default;
		GameManager & operator=(const GameManager &) = default;
		GameManager(GameManager &&)                  = default;
		GameManager & operator=(GameManager &&)      = default;

	public:

		/// <summary>
		/// �V���O���g���Ƃ��ĊǗ����Ă���GameManager�̃C���X�^���X���擾���܂��B
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static GameManager & Instance()
		{
			static GameManager gameManager;
			return gameManager;
		}

		/// <summary>
		/// GameObject�𐶐�����֐���o�^���܂��B
		/// </summary>
		static void setObjMap();

	private:

		/// <summary>
		/// �G���[���b�Z�[�W���o�͂��܂��B
		/// </summary>
		/// <param name="message"> ���b�Z�[�W </param>
		static void printError(const String & message)
		{
#ifdef _DEBUG
			Println(message);
#endif // _DEBUG
		}

		/// <summary>
		/// �^��gameObjectType��unique_ptr�����֐����}�b�v�ɓo�^���܂��B
		/// </summary>
		/// <param name="name"> �I�u�W�F�N�g�̖��O </param>
		template<typename gameObjectType>
		static void makeGenerateFunc(const String & name)
		{
			genarateEnemyMap[name] = GenerateFunc
			(
				[](const Vec2 & pos)
				{
					return std::make_unique<gameObjectType>(pos);
				}
			);
		}

		/// <summary>
		/// �w�肳�ꂽ�s������W���擾���܂��B
		/// </summary>
		/// <param name="csvReader"> CSVReader </param>
		/// <param name="readingRow"> �w�肷��s </param>
		/// <returns> ���W��Optional </returns>
		Optional<Vec2> getPointFromCSVReader(const CSVReader & csvReader, size_t readingRow);

		/// <summary>
		/// ������
		/// </summary>
		void init();

	public: // GameScene�Ŏg�p����֐�

		/// <summary>
		/// �Q�[���f�[�^���L�q����csv�t�@�C����ǂݍ��݂܂��B
		/// </summary>
		/// <param name="gameDataFileName"> csv�t�@�C���̖��O </param>
		void load(const String & gameDataFileName);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// �V�[���J�ڐ�������āA�V�[���J�ڂ��\�������܂��B
		/// </summary>
		/// <param name="sceneName"> �V�[���̖��O </param>
		/// <param name="sceneInfo"> �J�ڐ�ł̕⑫��� </param>
		/// <returns> �J�ډ\�ȂƂ� true , �����łȂ��Ƃ� false </returns>
		bool isChangeAbleScene(String & sceneName, String & sceneInfo) const;

	public: // GameState�Ŏg�p����֐�

		/// <summary>
		/// �X�e�[�W����ݒ肵�܂�
		/// </summary>
		void setStageName(const String & name)
		{
			_stageName = name;
		}

		/// <summary>
		/// �X�e�[�W�����擾���܂�
		/// </summary>
		const String & getStageName() const
		{
			return _stageName;
		}

		/// <summary>
		/// �I�u�W�F�N�g�ƌ��̍X���s���܂��B
		/// </summary>
		void updateObjectAndLight();

		/// <summary>
		/// �I�u�W�F�N�g�ƌ��̕`����s���܂��B
		/// </summary>
		void drawObjectAndLight()const;

		/// <summary>
		/// gameState��ύX���܂��B
		/// </summary>
		/// <param name="gameState"> gameState��unique_ptr </param>
		void changeGameState(StatePtr gameState)
		{
			_gameState = std::move(gameState);
		}

		/// <summary>
		/// �V�[���̐ݒ���ݒ肵�܂��B
		/// </summary>
		void setSceneName(const String & sceneName, const String & sceneInfo);

		/// <summary>
		/// �`���[�g���A���p�̃S�[�����쐬���܂��B
		/// </summary>
		void makeTutorialGoal();

	public: // GameObject�Ŏg�p����֐�

		/// <summary>
		/// �o�H���擾���܂��B
		/// </summary>
		/// <param name="posS"> �n�_ </param>
		/// <param name="posT"> �I�_ </param>
		/// <returns> �o�H��ōŏ��ɐi�ޕ��� </returns>
		Vec2 getPath(const Vec2 & posS, const Vec2 & posT) const
		{
			return _stageData.getPath(posS, posT);
		}

		/// <summary>
		/// 2�_�Ԃ̋������擾���܂��B
		/// </summary>
		/// <param name="posS"> �n�_ </param>
		/// <param name="posT"> �I�_ </param>
		/// <returns> ���� </returns>
		double getDistance(const Vec2 & posS, const Vec2 & posT) const
		{
			return _stageData.getDistance(posS, posT);
		}

		/// <summary>
		/// �����ꂽ���W���s���\�������܂��D
		/// </summary>
		/// <param name="pos"> ���W </param>
		/// <returns> �s���\�ȂƂ� true , �����łȂ��Ƃ� false </returns>
		bool isWalkingAblePos(const Vec2 & pos) const
		{
			if (pos.x < 0 || pos.y < 0) { return false; }
			return _stageData.isWalkAble(pos.asPoint() / _stageData.SIZE);
		}

		/// <summary>
		/// �v���C���[�̍��W��ݒ肵�܂��B
		/// </summary>
		/// <param name="playerPos"> �v���C���[�̍��W </param>
		void setPlayerPos(const Vec2 & playerPos)
		{
			_playerPos = playerPos;
		}

		/// <summary>
		/// �v���C���[�̍��W���擾���܂��B
		/// </summary>
		const Vec2 & getPlayerPos() const
		{
			return _playerPos;
		}

		/// <summary>
		/// �S�[���̍��W��ݒ肵�܂��B
		/// </summary>
		/// <param name="goalPos"> �S�[���̍��W </param>
		void setGoalPos(const Vec2 & goalPos)
		{
			_goalPos = goalPos;
		}

		/// <summary>
		/// �S�[���̍��W���擾���܂��B
		/// </summary>
		/// <returns> �S�[���̍��W </returns>
		const Vec2 & getGoalPos() const
		{
			return _goalPos;
		}

		/// <summary>
		/// ���̒��S���W��ݒ肵�܂��B
		/// </summary>
		/// <param name="pos"> ���̒��S���W </param>
		void setLightPos(const Vec2 & pos)
		{
			_light.setPos(pos);
		}

		/// <summary>
		/// ���̒��S���W���擾���܂��B
		/// </summary>
		const Vec2 & getLightPos() const
		{
			return _light.getPos();
		}

		/// <summary>
		/// �Q�[���N���A
		/// </summary>
		void gameClear();

		/// <summary>
		/// �Q�[���I�[�o�[
		/// </summary>
		void gameOver();

	};
}