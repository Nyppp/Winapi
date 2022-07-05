#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID; //���� ��� -> ��ü ����x -> �׻� ������ ������ ������

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

	//�׷��� ��������ڸ� ȣ�� ��, ������ ID���� ���� ��ü�� ������ ������ ����� -> ���� ������ ���� ����
	UINT m_iID; //�浹ü�� ������ id�� -> ���������� �浹 ������ �����ϱ� ���� ����

	//�浹ü�� ���� ���� ���� �� �ֱ⿡, �浹���θ� ǥ���ϴ� ��������� int�� ���� ����
	int m_iCol;

	
public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	UINT GetID() { return m_iID; }

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

public:
	void finalupdate();

	void render(HDC _dc);

	//���� �������� ����� ������Ŵ -> ������ ������
	CCollider& operator = (CCollider& _origin) = delete;

	void OnCollision(CCollider* _pOther); //�浹 ���� �� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther); //�浹 ���� �� ȣ��Ǵ� �Լ�
	void OnCollisionExit(CCollider* _pOther); //�浹�� ���� �� ȣ��Ǵ� �Լ�


	friend class CObject;
};

