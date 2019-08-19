#pragma once


#include "../GameManager.h"


namespace Robot
{
	class AccessState : public GameState
	{
	private:

		int _framecount; // �o�߃t���[����

		int _alpha;      // �A���t�@�l

		int _stageId;    // �X�e�[�W�ԍ�

		std::unique_ptr<GameState> _nextState; // ���̏��

	public:

		AccessState(bool isTutorial);

	private:

		void update() override;

		void draw() const override;

	};
}