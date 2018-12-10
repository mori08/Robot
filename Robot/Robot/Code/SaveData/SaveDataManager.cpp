#include "SaveDataManager.h"


namespace
{
	const int BASE    = 0x10;      // �Í����̊�ɂȂ�l(���i���ňÍ������邩)
	const int MUL     = BASE - 1;  // �|���Z�̂Ƃ��̂����鐔
	const int HALF    = BASE / 2;  // ��l�̔���
	const int MOD     = BASE*BASE; // �]����Ƃ�Ƃ��̊��鐔 
	const int MAX_KEY = MOD - 1;   // �L�[�̍ő�l
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
