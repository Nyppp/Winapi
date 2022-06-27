#pragma once

struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		//������ ���̸� ���Ѵ�.
		return sqrt(x * x  + y * y);
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

public:
	//POINT ����ü�� Vec2�� ���Թޱ� ���� ���Կ����� �����ε�
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

public:
	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}

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