#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	SaveDataManager�N���X
	SaveData�̃��[�h��Z�[�u�A
	�t���O�̕ύX�A�擾���s���܂��B
	*/
	class SaveDataManager
	{
	public:

		enum class LoadResult
		{
			NEW_GAME,
			CONTINUE,
			ERROR
		};

	private:
		
		static const int FLAG_NUM = 1;        // �t���O�̌�

		std::array<bool, FLAG_NUM> _flagList; // �t���O�̃��X�g

		std::unordered_map<String, int> _key; // ������Ɣz��̃C���f�b�N�X�̃}�b�v

	private:

		SaveDataManager();

		SaveDataManager(const SaveDataManager &)            = default;
		SaveDataManager & operator=(const SaveDataManager&) = default;
		SaveDataManager(SaveDataManager&&)                  = default;
		SaveDataManager & operator=(SaveDataManager&&)      = default;

	public:

		/// <summary>
		/// �V���O���g���Ƃ��ĊǗ����Ă���SaveDataManager�̃C���X�^���X���擾���܂��B
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static SaveDataManager & Instance()
		{
			static SaveDataManager saveDataManager;
			return saveDataManager;
		}

		/// <summary>
		/// ���[�h���܂��B
		/// </summary>
		const LoadResult & load();

		/// <summary>
		/// �Z�[�u���܂��B
		/// </summary>
		void save();

	private:

		/// <summary>
		/// �t���O�̃��X�g���Í������܂��B
		/// </summary>
		/// <returns> �t���O�̃��X�g���Í������������� </summary>
		const String & encryption() const;

		/// <summary>
		/// �Í����𕜍����A�t���O�̃��X�g�Ɋi�[���܂��B
		/// </summary>
		/// <param name="str"> �Í��� </param>
		/// <returns> �����ɐ��������Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool decryption(const String & str);

		/// <summary>
		/// String�^�̕������16�i���Ƃ��ēǂ�int�^�̐����l�ɕϊ����܂��B
		/// </summary>
		/// <param name="str"> ������ </param>
		/// <returns> �ϊ���̐��� �ϊ��Ɏ��s�����Ƃ� none </returns>
		static Optional<int> strToHex(const String & str);

	};
}