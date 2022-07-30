#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	//벡터 값
	Vec2 m_vForce; //벡터를 방향 + 크기가 담긴 정보로 사용
	Vec2 m_vAccel; //가속도 (F = m*a)
	Vec2 m_vVelocity; //속도(방향까지 담긴 정보)


	//스칼라 값
	float m_fMaxSpeed; //최대 속력
	float m_fMass; //질량
	float m_fSpeed; //속력(순수한 속력, 스칼라값)
	float m_fFricCoeff; //마찰 계수(힘 주는 방향에 대해 반대로 작용하는 반발)

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

