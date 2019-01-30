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
	TextureAsset(_textureName)(_texturePos*_textureSize, _textureSize).draw(_pos + shakeSize);
}


void Robot::ChangeTextureObject::changeTextureName(const String & name, const Size & size)
{
	_textureName = name;
	_textureSize = size;
}


void Robot::ChangeTextureObject::setUpdateTexture(size_t span, const std::vector<Point> & texturePosList)
{
	_isActing = false;
	size_t nextPosId = ((size_t)_actFrameCount / span) % texturePosList.size(); // 次に表示する画像の番号のインデックス

	_texturePos = texturePosList[nextPosId];
}


void Robot::ChangeTextureObject::changeTextureAct(size_t span, const std::vector<Point>& texturePosList)
{
	size_t nextPosId = _actFrameCount / span; // 次に表示する画像の番号のインデックス

	if (nextPosId >= (int)texturePosList.size())
	{
		finishAct();
		return;
	}

	_texturePos = texturePosList[nextPosId];
}
