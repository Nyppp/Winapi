#include "global.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr), m_fMass(1.f)
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
