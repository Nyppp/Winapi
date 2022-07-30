#include "global.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	//기본값 -> 질량 1 / 최대 속도 200.f/ 마찰계수 100.f
	: m_pOwner(nullptr), m_fMass(1.f), m_fMaxSpeed(200.f), m_fFricCoeff(100.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	float fForce = m_vForce.Length(); //힘의 크기

	if (fForce != 0.f)
	{
		m_vForce.normalize(); //힘의 방향

		float m_fAccel = fForce / m_fMass; //가속도 크기(a = f/m)

		m_vAccel = m_vForce * m_fAccel; //가속도 벡터

		m_vVelocity += m_vAccel * fDT; //속도 -> 가속도 만큼 계속해서 더하면, 가속도 운동에 의한 속도가 계산됨 (V = a + dt)
	}

	//마찰력 적용한 반대 방향으로의 가속도
	if (m_vVelocity.IsZero() != true) //힘이 들어오지 않았지만 속도는 0이 아닌 경우에 동작(코드로 속도 입력)
	{
		Vec2 vFricDir = m_vVelocity;
		Vec2 vFriction = -vFricDir.normalize() * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			//마찰 가속도가 힘보다 클 때(밀리지 않음)
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			//그 외에는, 밀림
			m_vVelocity += vFriction;
		}

		//최대 속도가 넘어가면 속도 조정
		if (m_vVelocity.Length() > m_fMaxSpeed)
		{
			m_vVelocity.normalize();
			m_vVelocity *= m_fMaxSpeed;
		}
	}

	Move();
	//힘을 전달한 뒤에는 힘의 값을 0으로 만든다 -> 이미 힘을 줘서 밀어냈기에
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	//속도 벡터를 분해한다면, 아래와 같이 2개로 분해 가능.
	//속력
	float fSpeed = m_vVelocity.Length();

	if (fSpeed != 0.f)
	{
		//방향
		Vec2 vDir = m_vVelocity;
		vDir.normalize(); //레퍼런스로 원본을 수정하기에 지역변수 수정

		Vec2 vPos = m_pOwner->GetPos();

		//실사용 - 속도 벡터에 단위시간만큼 곱한 값을 오브젝트의 위치로 설정
		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}
}
