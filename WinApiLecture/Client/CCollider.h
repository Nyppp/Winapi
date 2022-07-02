#pragma once

class CObject;

class CCollider
{
private:
	//�浹ü�� � ������Ʈ�� �浹ü���� �����ϱ� ����,
	//����Լ��� ������Ʈ ��ü�� ������.
	CObject* m_pOwner;
	
	//������ -> fps ���ӿ��� ��弦 ���а��� ����� ����
	//�浹ü ��ġ�� �� ������Ʈ ��ġ�� �ƴ϶�, �������� �ξ
	//���� ��ġ�� �浹 ��ġ�� ���̸� ��
	Vec2 m_vOffsetPos;

	//���� �����°�, ������Ʈ�� ��ġ�� ����� ���� �浹ü�� ��ġ
	Vec2 m_vFinalPos;

	//ũ��� ���밪���� ����
	Vec2 m_vScale;

public:
	CCollider();
	~CCollider();

public:
	void finalupdate();

	friend class CObject;
};

