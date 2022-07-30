#pragma once

//2D 좌표계에서 사용될 벡터 구조체 -> 화면의 좌표를 나타낸다.
struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		//벡터의 길이를 구한다.
		return (float)sqrt((double)x * (double)x + (double)y * (double)y);
	}

	//정규화 벡터 구하는 함수
	Vec2& normalize()
	{
		float fLen = Length();

		//영벡터에 대한 정규화는 assert로 접근 제한
		assert(fLen != 0.f);

		//각 성분을 길이로 나누면 정규화 벡터가 나옴
		x /= fLen; 
		y /= fLen;

		return *this;
	}

	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
		{
			return true;
		}
		return false;
	}

public:
	//POINT 구조체를 Vec2가 대입받기 위해 대입연산자 오버로딩
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	//벡터 구조체에 대한 연산자 오버로딩
	Vec2 operator + (Vec2 _pt)
	{
		return Vec2(x + _pt.x, y + _pt.y);
	}

	Vec2 operator - (Vec2 _pt)
	{
		return Vec2(x - _pt.x, y - _pt.y);
	}

	Vec2 operator * (Vec2 _pt)
	{
		return Vec2(x * _pt.x, y * _pt.y);
	}

	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	Vec2 operator / (Vec2 _pt)
	{
		if (_pt.x == 0.f || _pt.y == 0.f)
		{
			assert(false);
		}
		return Vec2(x / _pt.x, y / _pt.y);
	}

	Vec2 operator / (float _f)
	{
		if (_f == 0.f)
		{
			assert(false);
		}
		return Vec2(x / _f, y / _f);
	}

	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}

	void operator += (Vec2 _pt)
	{
		x += _pt.x;
		y += _pt.y;
	}

	void operator -= (Vec2 _pt)
	{
		x -= _pt.x;
		y -= _pt.y;
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

public:
	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}

	//벡터 구조체에 대한 복사 생성자

	//벡터 값은 데이터 상으로는 실수 이지만, 윈도우 환경으로 인자를 전달할 때는 정수타입.
	//정수를 입력받았을 때의 구조체 생성자를 통해 타입 캐스팅을 하면 된다.
	Vec2(int _x, int _y) 
	{
		x = (float)_x;
		y = (float)_y;
	}

	//또한 객체 선언과 동시에 POINT 객체를 대입하면, 복사 생성자를 호출하기 떄문에 생성자도 선언
	Vec2(POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}
};