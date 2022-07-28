#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2 m_vForce; //벡터를 방향 + 크기가 담긴 정보로 사용
	Vec2 m_vAccel; //가속도 (F = m*a)
	float m_fMass; //질량

	Vec2 m_vVelocity; //속도(방향까지 담긴 정보)
	float m_fSpeed; //속력(순수한 속력, 스칼라값)

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

