#pragma once

class CMonster;

//팩토리 메서드 패턴 -> 기능은 있지만 객체를 생성할 일은 없음

//몬스터의 종류 열거체
enum class MON_TYPE
{
	NORMAL,
	RANGE,
};

class CMonFactory
{
public:
	//객체의 생성 없이 접근하기 위해서, static 멤버함수 선언
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos);

public:
	//객체 생성을 막기 위해서 생성자, 소멸자를 빈 공간으로 정의
	CMonFactory() {};
	~CMonFactory() {};
};

