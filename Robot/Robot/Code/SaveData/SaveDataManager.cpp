#include "SaveDataManager.h"


namespace
{
	const int BASE    = 0x10;      // 暗号化の基準になる値(何進数で暗号化するか)
	const int MUL     = BASE - 1;  // 掛け算のときのかける数
	const int HALF    = BASE / 2;  // 基準値の半分
	const int MOD     = BASE*BASE; // 余りをとるときの割る数 
	const int MAX_KEY = MOD - 1;   // キーの最大値

	const int ONE_DATA_LENGTH = 2; // 暗号文における1データのとる文字数
}


const String & Robot::SaveDataManager::encryption() const
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
		rtn += ToString(data, BASE);
	}
}


bool Robot::SaveDataManager::decryption(const String & str)
{
	std::list<int> dataList;

	// to int array
	for (size_t i = 0; i < str.length; i += ONE_DATA_LENGTH)
	{
		Optional<int> data = strToHex(str.substr(i, ONE_DATA_LENGTH));		
		if(!data) { return false; }
		dataList.emplace_back(data);
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
	if (*dataList.begin() != *dataList.rbegin()) { return false; }
	dataList.pop_front();
	dataList.pop_back();

	// div 0xF
	for (auto && data : dataList)
	{
		if (data%MUL != 0) { return false; }
		data /= MUL;
		if (data <= 0x0 || data > BASE) { return false; }
	}

	// even number -> 0 , odd number -> 1
	for (auto && data : dataList)
	{
		data %= 2;
	}

	// 0 -> false , 1 -> true
	if (dataList.size() != _flagList.size()) { return false; }
	for (auto && flag : _flagList)
	{
		flag = *dataList.begin() == 0 ? false : true;
		dataList.pop_front();
	}

	return true;
}


Optional<int> Robot::SaveDataManager::strToHex(const String & str)
{
	int rtn = 0;

	for (const auto c : str)
	{
		rtn *= 0xF;

		if (c >= L'0' && c <= L'9')
		{
			rtn += static_cast<int>(c - L'0');
		}
		else if (c >= L'a' && c <= L'f')
		{
			rtn += static_cast<int>(c - L'a');
		}
		else
		{
			return none;
		}
	}

	return rtn;
}
