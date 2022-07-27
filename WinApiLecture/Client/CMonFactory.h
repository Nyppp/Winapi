#pragma once

class CMonster;

//���丮 �޼��� ���� -> ����� ������ ��ü�� ������ ���� ����

//������ ���� ����ü
enum class MON_TYPE
{
	NORMAL,
	RANGE,
};

class CMonFactory
{
public:
	//��ü�� ���� ���� �����ϱ� ���ؼ�, static ����Լ� ����
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos);

public:
	//��ü ������ ���� ���ؼ� ������, �Ҹ��ڸ� �� �������� ����
	CMonFactory() {};
	~CMonFactory() {};
};

