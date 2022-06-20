#pragma once

//��ũ�� �Լ� -> ��ó���� �������� �ش� ADD������ ������ �ڵ�� �ٲ���
//�Լ� ȣ���� �ƴ�, �ڵ� ġȯ���� ������ ����
#define ADD(a,b) a+b

//���� �Լ��� ADD(10,10) = 20��.
//������, 10 * ADD(10,10) -> 10 * 10 + 10 = 110�� ��(200�� �ǵ��ϰ� ����� ��� ����)

//��ü�� �����ϴ� GetInst() �Լ��� ��ũ�η� ����
//��ó���� �������� \�� ���̸� ���� �� ������ �����Ͽ� �д´ٴ� ����
// ***Unreal Engine ��ũ���Լ� ��İ� ����(UFUNCTION)***
#define SINGLE(type) public: \
					static type* GetInst()\
					{\
						static type mgr; return &mgr;\
					}\
					private:\
						type();\
						~type();