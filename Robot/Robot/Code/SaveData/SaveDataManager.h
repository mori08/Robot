#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	SaveDataManagerクラス
	SaveDataのロードやセーブ、
	フラグの変更、取得を行えます。
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
		
		static const int FLAG_NUM = 4;            // フラグの個数

		std::array<bool, FLAG_NUM> _flagList;     // フラグのリスト

		std::unordered_map<String, int> _nameMap; // 文字列と配列のインデックスのマップ

	private:

		SaveDataManager();

		SaveDataManager(const SaveDataManager &)            = default;
		SaveDataManager & operator=(const SaveDataManager&) = default;
		SaveDataManager(SaveDataManager&&)                  = default;
		SaveDataManager & operator=(SaveDataManager&&)      = default;

	public:

		/// <summary>
		/// シングルトンとして管理しているSaveDataManagerのインスタンスを取得します。
		/// </summary>
		/// <returns> インスタンス </returns>
		static SaveDataManager & Instance()
		{
			static SaveDataManager saveDataManager;
			return saveDataManager;
		}

		/// <summary>
		/// ロードします。
		/// </summary>
		LoadResult load();

		/// <summary>
		/// セーブします。
		/// </summary>
		void save();

		/// <summary>
		/// フラグを変更します。
		/// </summary>
		/// <param name="name"> フラグの名前 </param>
		/// <param name="value"> 変更後の値 </param>
		void setFlag(const String & name, bool value)
		{
#ifdef _DEBUG
			if (_nameMap.find(name) == _nameMap.end())
			{
				Println(L"Error > setFlag関数で存在しないフラグが指定されました。 : ", name);
				return;
			}
#endif // _DEBUG
			_flagList[_nameMap[name]] = value;
		}

		/// <summary>
		/// フラグを取得します。
		/// </summary>
		/// <param name="name"> フラグの名前 </param>
		/// <returns> 指定したフラグ </param>
		bool getFlag(const String & name)
		{
#ifdef _DEBUG
			if (_nameMap.find(name) == _nameMap.end())
			{
				Println(L"Error > setFlag関数で存在しないフラグが指定されました。 : ", name);
				return false;
			}
#endif // _DEBUG
			return _flagList[_nameMap[name]];
		}

		/// <summary>
		/// フラグの一覧を表示します。
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
		/// フラグのリストを暗号化します。
		/// </summary>
		/// <returns> フラグのリストを暗号化した文字列 </summary>
		String encryption() const;

		/// <summary>
		/// 暗号文を復号し、フラグのリストに格納します。
		/// </summary>
		/// <param name="str"> 暗号文 </param>
		/// <returns> 復号に成功したとき true , そうでないとき false </returns>
		bool decryption(const String & str);

		/// <summary>
		/// 文字列と配列のインデックスのマップを設定します。
		/// </summary>
		/// <param name="str"> indexに対応する文字列 </param>
		/// <param name="index"> _flagListに対応するインデックス </param>
		void setKey(const String & str, int index)
		{
#ifdef _DEBUG
			if (index < 0 || index >= FLAG_NUM)
			{
				Println(L"Error > setKey関数で不適切なindexが入力されました。 : ", index);
				return;
			}
			if (_nameMap.find(str) != _nameMap.end())
			{
				Println(L"Error > setKey関数で同じ文字列を登録しようとしました。 : ", str);
				return;
			}
#endif // _DEBUG
			_nameMap[str] = index;
		}

	};
}