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

	UINT m_iID; //�浹ü�� ������ id�� -> ���������� �浹 ������ �����ϱ� ���� ����
	
public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	CCollider();
	~CCollider();

public:
	void finalupdate();

	void render(HDC _dc);

	friend class CObject;
};

