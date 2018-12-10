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
	private:
		
		static const int FLAG_NUM = 1;        // フラグの個数

		std::array<bool, FLAG_NUM> _flagList; // フラグのリスト

		std::unordered_map<String, int> _key; // 文字列と配列のインデックスのマップ

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

	private:

		/// <summary>
		/// フラグのリストを暗号化します。
		/// </summary>
		/// <returns> フラグのリストを暗号化した文字列 </summary>
		const String & encryption() const;

	};
}