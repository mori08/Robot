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

		static const Act noAct; // ���o���Ȃ��Ƃ�

	protected:

		Point  _pos;                // ���W

		Range  _moveRange;          // �ړ��̎��_�ƏI�_

		int    _moveFrameCount;     // �ړ����̃t���[����

		int    _spanMoveFrameCount; // �ړ��ɂ�����̃t���[����

		ActMap _actMap;             // ���o�p�̊֐��̃}�b�v

		bool   _isActing;           // ���o���� true , �����łȂ��Ƃ� false

		int    _actFrameCount;      // ���o���̃t���[����

		Act    _act;                // ���o

		String _textureName;        // �\������摜�̖��O

	public:

		EventObject();

		/// <summary>
		/// �I�u�W�F�N�g�̈ړ���ݒ肵�܂��B
		/// </summary>
		/// <param name="goal"> �ړ���̍��W </param>
		/// <param name="spanFrameCount"> �ړ��ɂ�����t���[���� (0�̂Ƃ��͂����ړ�) </param>
		void setLinearMove(const Point & goal, int spanFrameCount = 0);

		/// <summary>
		/// �ړ��Ɖ��o���I�����Ă��邩�����܂��B
		/// </summary>
		/// <returns> �I�����Ă���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool completeMoveAndAct() const
		{
			return _isActing && _moveFrameCount > _spanMoveFrameCount;
		}

		/// <summary>
		/// ���o��o�^���܂��B
		/// </summary>
		/// <param name="actName"> ���o�̖��O </param>
		void setAct(const String & actName);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const;

	private:

		void moveObject();

	};
}