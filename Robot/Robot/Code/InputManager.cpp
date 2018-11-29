#include "InputManager.h"


void Robot::InputManager::resetInputList()
{
	// ‘S“ü—Í‚ðfalse‚É‚µ‚Ü‚·B
	for (auto itrW = _inputList.begin(); itrW != _inputList.end(); ++itrW)
	{
		for (auto itrH = itrW->second.begin(); itrH != itrW->second.end(); ++itrH)
		{
			itrH->second = false;
		}
	}


}


void Robot::InputManager::registerButton(const String & key, const Rect & region)
{
	_buttonList[key] = std::make_shared<Button>(key, region);
}
