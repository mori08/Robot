#include "SaveDataManager.h"


namespace
{
	const String SAVE_DATA_TEXT = L"SAVE-DATA.txt"; // セーブデータのファイル

	const int BASE    = 0x10;      // 暗号化の基準になる値(何進数で暗号化するか)
	const int MUL     = BASE - 1;  // 掛け算のときのかける数
	const int HALF    = BASE / 2;  // 基準値の半分
	const int MOD     = BASE*BASE; // 余りをとるときの割る数 
	const int MAX_KEY = MOD - 1;   // キーの最大値

	const int ONE_DATA_LENGTH = 2; // 暗号文における1データのとる文字数
}


Robot::SaveDataManager::SaveDataManager()
{
	setKey(L"Stage0", 0);
	setKey(L"Stage1", 1);
	setKey(L"Stage2", 2);
	setKey(L"Stage3", 3);
	setKey(L"Stage4", 4);
	setKey(L"Stage5", 5);
	setKey(L"Stage6", 6);
	setKey(L"Stage7", 7);
	setKey(L"Stage8", 8);
	setKey(L"Stage9", 9);
}


Robot::SaveDataManager::LoadResult Robot::SaveDataManager::load()
{
	TextReader reader(SAVE_DATA_TEXT);

	if (!reader.isOpened())
	{
		initOfNewGame();
		return LoadResult::NEW_GAME;
	}

	String str;

	if (reader.readLine(str) && decryption(str))
	{
		return LoadResult::CONTINUE;
	}

	return LoadResult::ERROR;
}


void Robot::SaveDataManager::initOfNewGame()
{
	for(auto && flag : _flagList)
	{
		flag = false;
	}
}


void Robot::SaveDataManager::save()
{
	TextWriter writer(SAVE_DATA_TEXT);

	writer.write(encryption());
}


String Robot::SaveDataManager::encryption() const
{
	std::list<int> dataList;

	// true -> 1 ,false -> 0
	for (const auto & flag : _flagList)
	{
		dataList.emplace_back(flag ? 1 : 0);
	}

	// 0 -> even number[0x2,0x10] , 1 -> odd number[0x1,0xF]
	for (auto && data : dataList)
	{
		data = 2 * (Random(0x1, HALF)) - data;
	}

	// mul 0xF
	for (auto && data : dataList)
	{
		data *= MUL;
	}

	// generate key
	int key = Random(0x0, MAX_KEY);

	// add key to dataList
	dataList.emplace_front(key);
	dataList.emplace_back(key);

	// add previous one and mod 0x100
	int previousOne = 0;
	for (auto && data : dataList)
	{
		data = (data + previousOne) % MOD;
		previousOne = data;
	}

	// to String
	String rtn;
	for(auto && data : dataList)
	{
		rtn += Pad(ToString(data, BASE), { 2,L'0' });
	}

	return rtn;
}


bool Robot::SaveDataManager::decryption(const String & str)
{
	std::list<int> dataList;

	// to int array
	for (size_t i = 0; i < str.length; i += ONE_DATA_LENGTH)
	{
		Optional<int> data = FromStringOpt<int>(str.substr(i, ONE_DATA_LENGTH), BASE);
		if(!data)
		{
			return false; 
		}
		dataList.emplace_back(*data);
	}

	// sub previous one and mod 0x100
	int previousOne = 0;
	for (auto && data : dataList)
	{
		int temp = data;
		data = (data - previousOne + MOD) % MOD;
		previousOne = temp;
	}

	// remove key
	if (*dataList.begin() != *dataList.rbegin()) 
	{
		return false; 
	}
	dataList.pop_front();
	dataList.pop_back();

	if (dataList.size() != _flagList.size())
	{
		return false;
	}

	// div 0xF
	for (auto && data : dataList)
	{
		if (data%MUL != 0)
		{ 
			return false; 
		}
		data /= MUL;
		if (data <= 0x0 || data > BASE) 
		{
			return false; 
		}
	}

	// even number -> 0 , odd number -> 1
	for (auto && data : dataList)
	{
		data %= 2;
	}

	// 0 -> false , 1 -> true
	for (auto && flag : _flagList)
	{
		flag = *dataList.begin() == 0 ? false : true;
		dataList.pop_front();
	}

	return true;
}
