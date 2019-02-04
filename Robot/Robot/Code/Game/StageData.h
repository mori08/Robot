#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	class StageData
	{
	private:

		static const int WIDTH  = 16;           // �X�e�[�W�̕�(�}�X)
		static const int HEIGHT = 12;           // �X�e�[�W�̍���(�}�X)
		static const int N      = WIDTH*HEIGHT; // �}�X�ڐ�
		static const int SIZE   = 40;           // �P�}�X�̑傫��(�s�N�Z��)

	private:

		std::array<bool, N>                _terrain;  // �n�` true�̂Ƃ���Q������

		std::array<std::array<Vec2, N>, N> _path;     // i��j �ւ̌o�H

	public:

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
		const Vec2 & getPath(const Vec2 & posS,const Vec2 & posT) const
		{
			int s = pointToInt(posS.asPoint() / SIZE);
			int t = pointToInt(posT.asPoint() / SIZE);
			return _path[s][t];
		}

		/// <summary>
		/// �n�`��o�H�̏������Z�b�g���܂��B
		/// </summary>
		void clear();

		/// <summary>
		/// �ǂ�ݒu���܂��B
		/// </summary>
		/// <param name="pos"> ���W </param>
		void setWall(const Point & pos)
		{
			_terrain[pointToInt(pos)] = true;
		}

		/// <summary>
		/// ���[�V�����E�t���C�h�@��p�����o�H�T�����s���܂��B
		/// </summary>
		void searchPath();

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