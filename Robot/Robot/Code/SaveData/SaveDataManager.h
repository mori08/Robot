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
		
		static const int FLAG_NUM = 10;           // �t���O�̌�

		std::array<bool, FLAG_NUM> _flagList;     // �t���O�̃��X�g

		std::unordered_map<String, int> _nameMap; // ������Ɣz��̃C���f�b�N�X�̃}�b�v

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
		LoadResult load();

		/// <summary>
		/// NewGame���̏��������s���܂��B
		/// </summary>
		void initOfNewGame();

		/// <summary>
		/// �Z�[�u���܂��B
		/// </summary>
		void save();

		/// <summary>
		/// �t���O��ύX���܂��B
		/// </summary>
		/// <param name="name"> �t���O�̖��O </param>
		/// <param name="value"> �ύX��̒l </param>
		void setFlag(const String & name, bool value)
		{
#ifdef _DEBUG
			if (_nameMap.find(name) == _nameMap.end())
			{
				Println(L"Error > setFlag�֐��ő��݂��Ȃ��t���O���w�肳��܂����B : ", name);
				return;
			}
#endif // _DEBUG
			_flagList[_nameMap[name]] = value;
		}

		/// <summary>
		/// �t���O���擾���܂��B
		/// </summary>
		/// <param name="name"> �t���O�̖��O </param>
		/// <returns> �w�肵���t���O </returns>
		bool getFlag(const String & name)
		{
#ifdef _DEBUG
			if (_nameMap.find(name) == _nameMap.end())
			{
				Println(L"Error > setFlag�֐��ő��݂��Ȃ��t���O���w�肳��܂����B : ", name);
				return false;
			}
#endif // _DEBUG
			return _flagList[_nameMap[name]];
		}

		/// <summary>
		/// �t���O�̈ꗗ��\�����܂��B
		/// </summary>
		void showFlagList()
		{
#ifdef _DEBUG
			for (auto & name : _nameMap)
			{
				Println(name.first, L" : ", _flagList[_nameMap[name.first]]);
			}
#endif // _DEBUG
		}

	private:

		/// <summary>
		/// �t���O�̃��X�g���Í������܂��B
		/// </summary>
		/// <returns> �t���O�̃��X�g���Í������������� </summary>
		String encryption() const;

		/// <summary>
		/// �Í����𕜍����A�t���O�̃��X�g�Ɋi�[���܂��B
		/// </summary>
		/// <param name="str"> �Í��� </param>
		/// <returns> �����ɐ��������Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool decryption(const String & str);

		/// <summary>
		/// ������Ɣz��̃C���f�b�N�X�̃}�b�v��ݒ肵�܂��B
		/// </summary>
		/// <param name="str"> index�ɑΉ����镶���� </param>
		/// <param name="index"> _flagList�ɑΉ�����C���f�b�N�X </param>
		void setKey(const String & str, int index)
		{
#ifdef _DEBUG
			if (index < 0 || index >= FLAG_NUM)
			{
				Println(L"Error > setKey�֐��ŕs�K�؂�index�����͂���܂����B : ", index);
				return;
			}
			if (_nameMap.find(str) != _nameMap.end())
			{
				Println(L"Error > setKey�֐��œ����������o�^���悤�Ƃ��܂����B : ", str);
				return;
			}
#endif // _DEBUG
			_nameMap[str] = index;
		}

	};
}