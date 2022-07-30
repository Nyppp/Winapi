#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	//���� ��
	Vec2 m_vForce; //���͸� ���� + ũ�Ⱑ ��� ������ ���
	Vec2 m_vAccel; //���ӵ� (F = m*a)
	Vec2 m_vVelocity; //�ӵ�(������� ��� ����)


	//��Į�� ��
	float m_fMaxSpeed; //�ִ� �ӷ�
	float m_fMass; //����
	float m_fSpeed; //�ӷ�(������ �ӷ�, ��Į��)
	float m_fFricCoeff; //���� ���(�� �ִ� ���⿡ ���� �ݴ�� �ۿ��ϴ� �ݹ�)

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

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMaxSpeed(float _f) { m_fMaxSpeed = _f; }

	float GetMass() { return m_fMass; }

private:
	void Move();

public:
	CObject* GetOwner() { return m_pOwner; }

	friend class CObject;
};

