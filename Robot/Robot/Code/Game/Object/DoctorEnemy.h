#pragma once


#include "DoctorDefence.h"
#include "DoctorSwitch.h"


namespace Robot
{
	/*
	DoctorEnemy�N���X
	�S�[���ƓG�𕡐�����
	�v���C���[���w��̍��W�ɗ������I�����ւ��鏈��������
	*/
	class DoctorEnemy : public GameObject
	{
	private:

		using DefenceList = std::list<std::unique_ptr<DoctorDefence>>;

		using SwitchList  = std::vector<DoctorSwitch>;

	private:

		double      _defenceRadian; // DoctorDefence�̉�]�̊p�x

		DefenceList _defenceList;   // DoctorDefence�̃��X�g

		SwitchList  _switchList;    // DoctorSwitch�̃��X�g

		int   _frameCount; // �o�߃t���[����

		Point _texturePos; // �\������摜�̔ԍ�

	public:

		DoctorEnemy(const Vec2 & pos);

		void update(GameManager & gameManager) override;

		void draw() const override;

	private:

		/// <summary>
		/// DoctorDefence�̖ړI�n�w��ƍX�V
		/// </summary>
		/// <param name="gameManager"> GameManager�̃C���X�^���X </param>
		void updateDefence(GameManager & gameManager);

		/// <summary>
		/// DoctorSwitch�̔���ƍX�V
		/// </summary>
		/// <param name="gameManager"> GameManager�̃C���X�^���X </param>
		void updateSwitch(GameManager & gameManager);

	};
}