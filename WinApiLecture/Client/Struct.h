#pragma once

//2D ��ǥ�迡�� ���� ���� ����ü -> ȭ���� ��ǥ�� ��Ÿ����.
struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		//������ ���̸� ���Ѵ�.
		return (float)sqrt((double)x * (double)x + (double)y * (double)y);
	}

	//����ȭ ���� ���ϴ� �Լ�
	Vec2& normalize()
	{
		float fLen = Length();

		//�����Ϳ� ���� ����ȭ�� assert�� ���� ����
		assert(fLen != 0.f);

		//�� ������ ���̷� ������ ����ȭ ���Ͱ� ����
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
	//POINT ����ü�� Vec2�� ���Թޱ� ���� ���Կ����� �����ε�
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	//���� ����ü�� ���� ������ �����ε�
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

	//���� ����ü�� ���� ���� ������

	//���� ���� ������ �����δ� �Ǽ� ������, ������ ȯ������ ���ڸ� ������ ���� ����Ÿ��.
	//������ �Է¹޾��� ���� ����ü �����ڸ� ���� Ÿ�� ĳ������ �ϸ� �ȴ�.
	Vec2(int _x, int _y) 
	{
		x = (float)_x;
		y = (float)_y;
	}

	//���� ��ü ����� ���ÿ� POINT ��ü�� �����ϸ�, ���� �����ڸ� ȣ���ϱ� ������ �����ڵ� ����
	Vec2(POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}
};