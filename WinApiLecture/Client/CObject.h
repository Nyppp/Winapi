#pragma once

class CCollider;

class CObject
{
private:
	//Ʈ������ ������ �Ǽ������� ������ ������, ������ �ÿ� ���������� ĳ����
	Vec2 m_vPos;
	Vec2 m_vScale;

	wstring m_strName;

	CCollider* m_pCollider;

	bool m_bAlive;

public:
	CObject();
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }

public:
	//�����Լ��� = 0 �� ���̸�, ������ �ڽ� ������Ʈ������ �������̵� ���θ� ���Ǹ� �� �� ����
	virtual void update() = 0;

	//�θ� ������Ʈ������ finalupdate��, �ڽ� ������Ʈ���� �������̵� �ϴ� �� �ƴ϶�
	//�θ� �������� �ڽ� ������Ʈ�� �ݶ��̴��� ������ �ִ��� ���θ� �˻��ϰ�, �ִٸ� �ݶ��̴��� ������Ʈ ��Ű�� ����
	//final Ű���� -> �ڽ� Ŭ�������� �������̵��� �ȵǸ�, �ش� ���������� ������ ������
	virtual void finalupdate() final;

	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	//������Ʈ�� �׾��ִ��� ���°� �ƹ� Ŭ���������� ���� ����������,
	bool IsDead() { return !m_bAlive; }

	//������Ʈ�� ���� ���·� ����� ���� �̺�Ʈ ������ Ŭ���������� ���� �����ϰ� �ؾ���.
	//�ƹ� Ŭ������ �����ϰ� �ϸ� ���� �߻�
private:
	void SetDead() { m_bAlive = false; }


public:
	void CreateCollider();

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	//������Ʈ�� ���ó���� �����ϱ� ���� friend ����
	friend class CEventMgr;
};

