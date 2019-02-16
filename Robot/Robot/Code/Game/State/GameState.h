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
		/// <param name="gameManager"> GameManager�̃C���X�^���X </param>
		virtual void update(GameManager & gameManager) = 0;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="gameManager"> GameManager�̃C���X�^���X </param>
		virtual void draw(const GameManager & gamaManager) const = 0;

	};
}