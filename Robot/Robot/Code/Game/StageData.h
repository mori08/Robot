#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	StageData�N���X
	GameManager�ň����n�`�̊Ǘ���
	�o�H�T�����s���܂��B
	*/
	class StageData
	{
	public:

		static const int WIDTH  = 16;           // �X�e�[�W�̕�(�}�X)
		static const int HEIGHT = 12;           // �X�e�[�W�̍���(�}�X)
		static const int N      = WIDTH*HEIGHT; // �}�X�ڐ�
		static const int SIZE   = 40;           // �P�}�X�̑傫��(�s�N�Z��)

	private:

		std::array<bool, N> _terrain;  // �n�` true�̂Ƃ���Q������

		std::array<std::array<Vec2,    N>, N> _path;     // i��j �ւ̌o�H
		std::array<std::array<double , N>, N> _distance; // i��j �ւ̋���

	public:

		/// <summary>
		/// Vec2���W����}�X��\������Point���W�ɕϊ����܂��B
		/// </summary>
		/// <param name="pos"> Vec2���W </param>
		/// <returns> �}�X��\������Point���W </returns>
		static Point translatePos(const Vec2 & pos);

		/// <summary>
		/// �}�X�̒��S���W���擾���܂��B
		/// </summary>
		/// <param name="pos"> �}�X��\������Point���W </param>
		/// <returns> Vec2���W </returns>
		static Vec2 centerPosOfCell(const Point & pos);

		/// <summary>
		/// ���W�����������l�����W�ɕϊ����܂��B
		/// </summary>
		/// <param name="i"> ���W�����������l </param>
		/// <returns> ���W </returns>
		static Point intToPoint(int i)
		{
			return std::move(Point(i % WIDTH, i / WIDTH));
		}

		/// <summary>
		/// ���W������ɑΉ����鐮���l�ɕϊ����܂��B
		/// </summary>
		/// <param name="pos"> ���W </param>
		/// <returns> ���W�����߂������l </returns>
		static int pointToInt(const Point & pos)
		{
			return pos.x + WIDTH*pos.y;
		}

	public:

		/// <summary>
		/// �����ꂽ���W���s���\�������܂��B
		/// </summary>
		/// <param name="pos"> ���W </param>
		/// <returns> �s���\�ȂƂ� true , �n�}�O�ł���Ƃ���ǂ�����Ƃ� false </returns>
		bool isWalkAble(const Point & pos) const
		{
			if (pos.x < 0 || pos.x >= WIDTH) return false;
			if (pos.y < 0 || pos.y >= HEIGHT)return false;
			return !_terrain[pointToInt(pos)];
		}

		/// <summary>
		/// �����ꂽ���W���s���\�������܂��B
		/// </summary>
		/// <param name="x"> x���W </param>
		/// <param name="y"> y���W </param>
		/// <returns> �s���\�ȂƂ� true , �n�}�O�ł���Ƃ���ǂ�����Ƃ� false </returns>
		bool isWalkAble(int x, int y) const
		{
			return isWalkAble(Point(x, y));
		}

		/// <summary>
		/// �����ꂽ���W���s���\�������܂��B
		/// </summary>
		/// <param name="i"> ���W�����������l </param>
		/// <returns> �s���\�ȂƂ� true , �n�}�O�ł���Ƃ���ǂ�����Ƃ� false </returns>
		bool isWalkAble(int i) const
		{
			return isWalkAble(intToPoint(i));
		}

		/// <summary>
		/// �o�H���擾���܂�
		/// </summary>
		/// <param name="posS"> �n�_ </param>
		/// <param name="posT"> �I�_ </param>
		/// <returns> �o�H��ōŏ��ɐi�ޕ��� </returns>
		Vec2 getPath(const Vec2 & posS, const Vec2 & posT) const;

		/// <summary>
		/// �������擾���܂�
		/// </summary>
		/// <param name="posS"> �n�_ </param>
		/// <param name="posT"> �I�_ </param>
		/// <returns> ���� </returns>
		double getDistance(const Vec2 & posS, const Vec2 & posT) const;


		/// <summary>
		/// �n�`��o�H�̏������Z�b�g���܂��B
		/// </summary>
		void clear();

		/// <summary>
		/// �ǂ�ݒu���܂��B
		/// </summary>
		/// <param name="x"> x���W </param>
		/// <param name="y"> y���W </param>
		void setWall(int x, int y)
		{
			_terrain[pointToInt(Point(x, y))] = true;
		}

		/// <summary>
		/// ���[�V�����E�t���C�h�@��p�����o�H�T�����s���܂��B
		/// </summary>
		void searchPath();

		/// <summary>
		/// �X�e�[�W�̕`��
		/// </summary>
		void draw() const;

	private:

		/// <summary>
		/// 2���_�Ԃ̕ӂ��擾���܂��B
		/// </summary>
		/// <param name="i"> �n�_�����������l </param>
		/// <param name="j"> �I�_�����������l </param>
		/// <returns> �� { ����,�R�X�g } </returns>
		/// <remarks> �ӂ����݂��Ȃ��Ƃ� { Vec2::Zero,INF } ��Ԃ��܂��B </remarks>
		std::pair<Vec2, double> getEdge(int i, int j) const;

	};
}