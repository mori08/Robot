#pragma once


namespace Robot
{
	class GameManager;

	/*
	GameState�N���X
	GameManager�ɂ�������
	*/
	class GameState
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