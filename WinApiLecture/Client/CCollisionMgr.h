#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	//�ִ� 32��(������Ʈ ����)��ŭ�� ������Ʈ�� �浹 ���踦 ��� �迭
	//��Ʈ �������� �����Ǿ� ������, ���� 0�� ������Ʈ�� 3�� ������Ʈ�� �浹 ���迡 �ְ� �������ʹ� �浹�� �ȵǴ� ������,
	//m_arrCheck[0] = 0000 0000 .... 0100 �� ���� �����(0x04)
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];

	//�浹ü ���� ���� �������� �浹 ����
	

public:
	void init();
	void update();

	//�� �׷��� �浹���踦 �����ϴ� �Լ�
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	//�浹���� �ʱ�ȭ
	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
	}

private:
	//�� ������Ʈ ������ �浹 ���踦 ������Ʈ�ϴ� �Լ�
	void CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	//�� ������Ʈ�� �浹�ߴ��� ���θ� ��ȯ�ϴ� �Լ�
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);

};

