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

		/// <summary>
		/// 暗号文を復号し、フラグのリストに格納します。
		/// </summary>
		/// <param name="str"> 暗号文 </param>
		/// <returns> 復号に成功したとき true , そうでないとき false </returns>
		bool decryption(const String & str);

		/// <summary>
		/// String型の文字列を16進数として読みint型の整数値に変換します。
		/// </summary>
		/// <param name="str"> 文字列 </param>
		/// <returns> 変換後の整数 変換に失敗したとき none </returns>
		static Optional<int> strToHex(const String & str);

	};
}