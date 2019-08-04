#include "ChangeTextureObject.h"


Robot::ChangeTextureObject::ChangeTextureObject(const Point & pos, const Point & texturePos, const Size & textureSize, const String & textureName)
	: EventObject(pos)
	, _texturePos(texturePos)
	, _textureSize(textureSize)
	, _textureName(textureName)
{

}


void Robot::ChangeTextureObject::draw(const Vec2 & shakeSize) const
{
	if (_isHidding) { return; }

	TextureAsset(_textureName)(_texturePos*_textureSize, _textureSize).draw(_pos + shakeSize);
}


void Robot::ChangeTextureObject::changeTextureName(const Size & size, const String & name)
{
	_textureSize = size;
	_textureName = name;
}


void Robot::ChangeTextureObject::setTextureUpdating(const size_t & span, const std::vector<Point> & texturePosList)
{
	_isActing = false;

#ifdef _DEBUG
	if (span == 0 || texturePosList.size() == 0)
	{
		Println(L"Error > updateTexture�ŕs�K�؂Ȓl���w�肳��܂����B");
		return;
	}
#endif // _DEBUG
	
	_texturePos = texturePosList[0];
	_act = std::make_shared<Act>([&]() { updateTexture(span, texturePosList); });
}


void Robot::ChangeTextureObject::updateTexture(const size_t & span, const std::vector<Point> & texturePosList)
{
	size_t nextPosId = ((size_t)_actFrameCount / span) % texturePosList.size(); // ���ɕ\������摜�̔ԍ��̃C���f�b�N�X

	_texturePos = texturePosList[nextPosId];
}


void Robot::ChangeTextureObject::changeTextureAct(const size_t & span, const std::vector<Point>& texturePosList)
{
	size_t nextPosId = _actFrameCount / span; // ���ɕ\������摜�̔ԍ��̃C���f�b�N�X

	if (nextPosId >= (int)texturePosList.size())
	{
		finishAct();
		return;
	}

	_texturePos = texturePosList[nextPosId];
}
