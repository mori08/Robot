#pragma once


#include "PoliceEnemy.h"
#include "MonitorState\MonitorState.h"


namespace Robot
{
	/*
	PatrolTeamEnemy�N���X
	PoliceEnemy�𕡐�����
	�����ň�������Player���G����
	PoliceEnemy����C�ɒǂ�������
	*/
	class PatrolTeamEnemy : public GameObject
	{
	private:

		using MonitorState = std::unique_ptr<MonitorState>;

		using PoliceList   = std::vector<PoliceEnemy>;

	private:

		Vec2         _monitorPos;   // �Ď��̌��̔��a

		MonitorState _monitorState; // �Ď��̌��̏��

		PoliceList   _policeList;   // PoliceEnemy�̔z��

	public:

		/// <summary>
		/// �Ď��`�[��
		/// </summary>
		/// <parma name="pos"> �������W </param>
		PatrolTeamEnemy(const Vec2 & pos);

		/// <summary>
		/// �Ď��p�̌��̏�Ԃ�؂�ւ���
		/// </summary>
		/// <param name="newState"> �V������� </param>
		void changeMonitorState(MonitorState && newState)
		{
			_monitorState = std::move(newState);
		}

		/// <summary>
		/// �Ď��p�̌��̍��W���擾
		/// </summary>
		const Vec2 & getMonitorPos() const
		{
			return _monitorPos;
		}

		/// <summary>
		/// PoliceEnemy�̋�����ς���
		/// </summary>
		/// <param name="isChasing"> true �Ȃ� �ǂ������� , false �Ȃ� �߂� </param>
		void setPoliceChasing(bool isChasing);

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

		void drawLight() const override;

	};
}