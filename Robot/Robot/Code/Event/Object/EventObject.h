#pragma once

#include<Siv3D.hpp>

namespace Robot
{
	/*
	EventObject�N���X
	Event�V�[���Ŏg�p����Object
	�`��E�ړ��E���̑��A�N�V��������������

	���̃N���X�̔h���N���X�����Ƃ���
	GenerateObject��setObjectMap�֐��ɓo�^����
	*/
	class EventObject
	{
	protected:

		using Range = std::pair<Point, Point>;             // �ړ��̎n�_�ƏI�_

		using Act    = std::function<void()>;              // ���o�p�֐�

		using ActPtr = std::shared_ptr<Act>;               // ���o�p�֐��̃|�C���^

		using ActMap = std::unordered_map<String, ActPtr>; // ���o�p�֐��̃|�C���^�̃}�b�v

		static const ActPtr noAct; // ���o���Ȃ��Ƃ�

	protected:

		Point  _pos;                // ���W

		Range  _moveRange;          // �ړ��̎��_�ƏI�_

		int    _moveFrameCount;     // �ړ����̃t���[����

		int    _spanMoveFrameCount; // �ړ��ɂ�����̃t���[����

		ActMap _initMap;            // �I�u�W�F�N�g�̏������p�̃}�b�v

		ActMap _actMap;             // ���o�p�̊֐��̃}�b�v

		bool   _isActing;           // ���o���� true , �����łȂ��Ƃ� false

		int    _actFrameCount;      // ���o���̃t���[����

		ActPtr _act;                // ���o

		bool   _isHidding;          // true �̂Ƃ���\��

	public:

		/// <summary>
		/// �C�x���g�I�u�W�F�N�g
		/// </summary>
		/// <param name="pos"> ���W </param>
		EventObject(const Point & pos);

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
			return !_isActing && _moveFrameCount > _spanMoveFrameCount;
		}

		/// <summary>
		/// �������֐������݂��邩�����܂��B
		/// </summary>
		/// <param name="name"> �������֐��̖��O </param>
		/// <returns> ���݂���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isExistedInit(const String & name) const
		{
			return _initMap.find(name) != _initMap.end();
		}

		/// <summary>
		/// ���o�����݂��邩�����܂��B
		/// </summary>
		/// <param name="name"> ���o�̖��O </param>
		/// <returns> ���݂���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isExistedAct(const String & name) const
		{
			return _actMap.find(name) != _actMap.end();
		}

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="initName"> �������֐��̖��O </param>
		void init(const String & initName);

		/// <summary>
		/// ���o��o�^���܂��B
		/// </summary>
		/// <param name="actName"> ���o�̖��O </param>
		void setAct(const String & actName);

		/// <summary>
		/// ��\���E�\����؂�ւ��܂��B
		/// </summary>
		/// <param name="hide"> true �̂Ƃ� ��\�� , false �̂Ƃ� �\�� </param>
		void setHide(bool hide)
		{
			_isHidding = hide;
		}

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update();

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shakeSize"> �U���̑傫�� </param>
		virtual void draw(const Vec2 & shakeSize) const = 0;

	protected:

		/// <summary>
		/// ���o���I�����܂��B
		/// </summary>
		void finishAct();

	private:

		/// <summary>
		/// �I�u�W�F�N�g�𓮂����܂��B
		/// </summary>
		void moveObject();

	};
}