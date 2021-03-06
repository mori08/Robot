#include "TitleLight.h"
#include "../MyColor.h"


namespace
{
	const int LONG_LENGTH  = 80; // 長い方の長さ
	const int SHORT_LENGTH = 5;  // 短い方の長さ

	const double SHADOW_BLUR_RADIUS = 20.0; // 影のぼかしの大きさ
	const double SHADOW_SPREAD      = 10.0; // 影の広がりかた

	const int DIRECTION_NUM = 4; // 光の進む方向の数
	const int UP    = 0; // 上
	const int DOWN  = 1; // 下
	const int LEFT  = 2; // 左
	const int RIGHT = 3; // 右
}


Robot::TitleLight::TitleLight(const Point & velocity, const Rect & region)
	: _region(region)
	, _velocity(velocity)
{
	
}


const Robot::TitleLight Robot::TitleLight::get()
{
	static int direction = 0;
	
	switch (++direction%DIRECTION_NUM)
	{
	case UP   : return Robot::TitleLight(Point::Up   , Rect(Random(Window::Width()), Window::Height()        , Size(SHORT_LENGTH, LONG_LENGTH )));
	case DOWN : return Robot::TitleLight(Point::Down , Rect(Random(Window::Width()), -LONG_LENGTH            , Size(SHORT_LENGTH, LONG_LENGTH )));
	case LEFT : return Robot::TitleLight(Point::Left , Rect(Window::Width()        , Random(Window::Height()), Size(LONG_LENGTH , SHORT_LENGTH)));
	case RIGHT: return Robot::TitleLight(Point::Right, Rect(-LONG_LENGTH           , Random(Window::Height()), Size(LONG_LENGTH , SHORT_LENGTH)));

	default:

#ifdef _DEBUG

		Println(L"Error > getでdirectionの値が指定外です。 : ", direction);

#endif // _DEBUG

		return Robot::TitleLight(Point::Zero, Rect());
	}
}


void Robot::TitleLight::update()
{
	_region.pos += _velocity;
}


void Robot::TitleLight::draw() const
{
	_region.drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}


bool Robot::TitleLight::isEraseAble() const
{
	if (_region.x < -LONG_LENGTH    ) { return true; }
	if (_region.x > Window::Width() ) { return true; }
	if (_region.y < -LONG_LENGTH    ) { return true; }
	if (_region.y > Window::Height()) { return true; }

	return false;
}
