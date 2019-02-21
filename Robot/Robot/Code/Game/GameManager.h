#pragma once


#include "StageData.h"
#include "Object\GameObject.h"
#include "State\GameState.h"
#include "GameLight.h"


namespace
{
	// �I�u�W�F�N�g�̃��X�g
	using ObjList = std::vector<std::unique_ptr<Robot::GameObject>>;

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

		StatePtr   _gameState; // ���

		StageData  _stageData; // �X�e�[�W�f�[�^

		ObjList    _objList;   // �I�u�W�F�N�g�̃��X�g

		GameLight  _light;     // ��

		Vec2       _playerPos; // �v���C���[�̍��W

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
		/// �I�u�W�F�N�g�ƌ��̍X���s���܂��B
		/// </summary>
		void updateObjectAndLight();

		/// <summary>
		/// �I�u�W�F�N�g�ƌ��̕`����s���܂��B
		/// </summary>
		void drawObjectAndLight()const;

		/// <summary>
		/// �V�[���̐ݒ���ݒ肵�܂��B
		/// </summary>
		void setSceneName(const String & sceneName, const String & sceneInfo);

	public: // GameObject�Ŏg�p����֐�

		/// <summary>
		/// �o�H���擾���܂��B
		/// </summary>
		/// <param name="posS"> �n�_ </param>
		/// <param name="posT"> �I�_ </param>
		/// <returns> �o�H��ōŏ��ɐi�ޕ��� </returns>
		const Vec2 & getPath(const Vec2 & posS, const Vec2 & posT) const
		{
			return _stageData.getPath(posS, posT);
		}

		/// <summary>
		/// �����ꂽ���W���s���\�������܂��D
		/// </summary>
		/// <param name="pos"> ���W </param>
		/// <returns> �s���\�ȂƂ� true , �����łȂ��Ƃ� false </returns>
		bool isWalkingAblePos(const Vec2 & pos) const
		{
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
		/// �Q�[���N���A
		/// </summary>
		void gameClear();

		/// <summary>
		/// �Q�[���I�[�o�[
		/// </summary>
		void gameOver();

	};
}