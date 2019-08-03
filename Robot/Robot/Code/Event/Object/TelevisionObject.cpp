#include "TelevisionObject.h"


namespace
{
	const Size  TEXTURE_SIZE  (190, 100); // 画像のサイズ
	const Point ON_TEXTURE_POS(1,0);      // テレビをつけているときの画像の番号

	const int LINE_RAND  = 30; // 影の線をだす頻度
	const int LINE_WIDTH = 1;  // 影の線の幅
}


Robot::TelevisionObject::TelevisionObject(const Point & pos)
	: EventObject(pos)
	, _texture(TextureAsset(L"TV")(Point::Zero, TEXTURE_SIZE))
	, _on(false)
{
	_initMap[L"On"] = std::make_shared<Act>([this]() {tvOn(); });
}


void Robot::TelevisionObject::draw(const Vec2 & shakeSize) const
{
	Vec2 pos = _pos + shakeSize;
	_texture.draw(pos);

	if (_on && Random(LINE_RAND) == 0)
	{
		RectF(pos.x, pos.y + Random(TEXTURE_SIZE.y), TEXTURE_SIZE.x, LINE_WIDTH).draw(Palette::MyBlack);
	}
}


void Robot::TelevisionObject::tvOn()
{
	_texture = TextureAsset(L"TV")(ON_TEXTURE_POS*TEXTURE_SIZE, TEXTURE_SIZE);
	_on = true;
}
