#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2 m_vForce; //���͸� ���� + ũ�Ⱑ ��� ������ ���
	Vec2 m_vAccel; //���ӵ� (F = m*a)
	float m_fMass; //����

	Vec2 m_vVelocity; //�ӵ�(������� ��� ����)
	float m_fSpeed; //�ӷ�(������ �ӷ�, ��Į��)

public:
	CRigidBody();
	~CRigidBody();

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF)
	{
		m_vForce += _vF;
	}

	void SetMass(float _fMass)
	{
		m_fMass = _fMass;
	}

	float GetMass() { return m_fMass; }

private:
	void Move();

public:
	CObject* GetOwner() { return m_pOwner; }

	friend class CObject;
};

