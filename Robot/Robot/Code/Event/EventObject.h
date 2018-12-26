#pragma once

#include<Siv3D.hpp>

namespace Robot
{
	/*
	EventObject�N���X
	Event�V�[���Ŏg�p����Object
	�`��E�ړ��E���̑��A�N�V��������������
	*/
	class EventObject
	{
	protected:

		using Range = std::pair<Point, Point>;

		using Act = std::shared_ptr<std::function<void()>>;

		using ActMap = std::unordered_map<String, Act>;

	protected:

		Point  _pos;                // ���W

		Range  _moveRange;          // �ړ��̎��_�ƏI�_

		bool   _isActing;           // ���o���� true , �����łȂ��Ƃ� false

		Act    _act;                // ���o

		int    _moveFrameCount;     // �ړ����̃t���[����

		int    _spanMoveFrameCount; // �ړ��ɂ�����̃t���[����

		ActMap _actMap;             // ���o�p�̊֐��̃}�b�v

	public:

		/// <summary>
		/// �I�u�W�F�N�g�̈ړ���ݒ肵�܂��B
		/// </summary>
		/// <param name="pos"> �ړ���̍��W </param>
		/// <param name="spanFrameCount"> �ړ��ɂ�����t���[���� </param>
		void setLinearMove(const Point & pos, int spanFrameCount);

		bool CompleteMoving() const
		{
			return _moveFrameCount > _spanMoveFrameCount;
		}

		/// <summary>
		/// ���o��o�^���܂��B
		/// </summary>
		/// <param name="actName"> ���o�̖��O </param>
		void setAct(const String & actName);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	};
}