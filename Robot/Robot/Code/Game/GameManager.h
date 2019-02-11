#pragma once


#include "GameManager.h"
#include "StageData.h"
#include "GameObject.h"
#include "GameLight.h"


namespace
{
	// �I�u�W�F�N�g�̃��X�g
	using ObjList = std::vector<std::unique_ptr<Robot::GameObject>>;
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

		StageData  _stageData; // �X�e�[�W�f�[�^

		ObjList    _objList;   // �I�u�W�F�N�g�̃��X�g

		GameLight  _light;     // ��

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

	public: // GameObject�Ŏg�p����֐�

		/// <summary>
		/// �o�H���擾���܂��B
		/// </summary>
		/// <param name="posS"> �n�_ </param>
		/// <param name="posT"> �I�_ </param>
		/// <returns> �o�H��ōŏ��ɐi�ޕ��� </returns>
		const Vec2 & getPath(const Vec2 & posS, const Vec2 & posT)
		{
			return _stageData.getPath(posS, posT);
		}

	};
}