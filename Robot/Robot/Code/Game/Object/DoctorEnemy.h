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

		using EnemyList   = std::vector<std::unique_ptr<GameObject>>;

	private:

		double      _defenceRadian; // DoctorDefence�̉�]�̊p�x

		DefenceList _defenceList;   // DoctorDefence�̃��X�g

		SwitchList  _switchList;    // DoctorSwitch�̃��X�g

		EnemyList   _enemyList;     // �X�C�b�`�������ꂽ�Ƃ��ɌĂяo�����I�u�W�F�N�g

		int   _frameCount; // �o�߃t���[����

		Point _texturePos; // �\������摜�̔ԍ�

	public:

		DoctorEnemy(const Vec2 & pos);

		void update() override;

		void draw() const override;

		void drawLight() const override;

	private:

		/// <summary>
		/// DoctorDefence�̖ړI�n�w��ƍX�V
		/// </summary>
		void updateDefence();

		/// <summary>
		/// DoctorSwitch�̔���ƍX�V
		/// </summary>
		void updateSwitch();

	};
}