#pragma once


#include <Siv3D.hpp>
#include "StageData.h"


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

		StageData _stageData; // �X�e�[�W�f�[�^

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
		/// �`��
		/// </summary>
		void draw() const;

	};
}