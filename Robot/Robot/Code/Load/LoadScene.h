#pragma once


#include "../Main.h"
#include <thread>


namespace Robot
{
	/*
	LoadScene�N���X
	���Ԃ̂����鏈����ʃX���b�h�ōs���܂��B

	*/
	class LoadScene : public MyApp::Scene
	{
	private:

		bool        _isLoading;  // ���[�h���̂Ƃ� true , �I�������Ƃ� false

		static int  _frameCount; // �o�߃t���[����

	protected:

		std::thread _loadThread; // ���[�h����X���b�h

	public:

		LoadScene();

		virtual ~LoadScene();

	public:

		void init() override;

		void update() override;

		void updateFadeIn(double) override;

		void updateFadeOut(double) override;

		void draw() const override;

		void drawFadeIn(double) const override;

		void drawFadeOut(double) const override;

	protected:

		/// <summary>
		/// _loadThread�œ������֐�
		/// </summary>
		virtual void load() = 0;

		/// <summary>
		/// �X���b�h�̏������I�������Ƃ��ɍs������
		/// </summary>
		/// <remarks> 
		/// �K��changeScene�֐���p����Scene�J�ڂ��s������ 
		/// </remarks>
		virtual void complete() = 0;

	};

}