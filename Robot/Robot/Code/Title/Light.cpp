#include "Light.h"
#include "../MyColor.h"


namespace
{
	const int LONG_LENGTH  = 80; // �������̒���
	const int SHORT_LENGTH = 5;  // �Z�����̒���

	const double SHADOW_BLUR_RADIUS = 20.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 10.0; // �e�̍L���肩��

	const int DIRECTION_NUM = 4; // ���̐i�ޕ����̐�
	const int UP    = 0; // ��
	const int DOWN  = 1; // ��
	const int LEFT  = 2; // ��
	const int RIGHT = 3; // �E
}


Robot::Light::Light(const Point & velocity, const Rect & region)
	: _region(region)
	, _velocity(velocity)
{
	
}


const Robot::Light Robot::Light::get()
{
	static int direction = 0;
	
	switch (++direction%DIRECTION_NUM)
	{
	case UP   : return Robot::Light(Point::Up   , Rect(Random(Window::Width()), Window::Height()        , Size(SHORT_LENGTH, LONG_LENGTH )));
	case DOWN : return Robot::Light(Point::Down , Rect(Random(Window::Width()), -LONG_LENGTH            , Size(SHORT_LENGTH, LONG_LENGTH )));
	case LEFT : return Robot::Light(Point::Left , Rect(Window::Width()        , Random(Window::Height()), Size(LONG_LENGTH , SHORT_LENGTH)));
	case RIGHT: return Robot::Light(Point::Right, Rect(-LONG_LENGTH           , Random(Window::Height()), Size(LONG_LENGTH , SHORT_LENGTH)));

	default:

#ifdef _DEBUG

		Println(L"Error > get��direction�̒l���w��O�ł��B : ", direction);

#endif // _DEBUG

		return Robot::Light(Point::Zero, Rect());
	}
}


void Robot::Light::update()
{
	_region.pos += _velocity;
}


void Robot::Light::draw() const
{
	_region.drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}


bool Robot::Light::isEraseAble() const
{
	if (_region.x < -LONG_LENGTH    ) { return true; }
	if (_region.x > Window::Width() ) { return true; }
	if (_region.y < -LONG_LENGTH    ) { return true; }
	if (_region.y > Window::Height()) { return true; }

	return false;
}
