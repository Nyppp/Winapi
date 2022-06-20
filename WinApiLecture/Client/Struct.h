#pragma once

struct Vec2
{
	float x;
	float y;

public:
	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}

	//벡터 값은 데이터 상으로는 실수 이지만, 윈도우 환경으로 인자를 전달할 때는 정수타입.
	//정수를 입력받았을 때의 구조체 생성자를 통해 타입 캐스팅을 하면 된다.
	Vec2(int _x, int _y) 
	{
		x = (float)_x;
		y = (float)_y;
	}

};