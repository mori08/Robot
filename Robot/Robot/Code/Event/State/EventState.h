#pragma once


namespace Robot
{
	/*
	EventState�N���X
	EventManager�ɂ�������
	*/
	class EventState
	{
	public:

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0;

	};
}