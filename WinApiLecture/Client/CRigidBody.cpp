#include "global.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	//�⺻�� -> ���� 1 / �ִ� �ӵ� 200.f/ ������� 100.f
	: m_pOwner(nullptr), m_fMass(1.f), m_fMaxSpeed(200.f), m_fFricCoeff(100.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	float fForce = m_vForce.Length(); //���� ũ��

	if (fForce != 0.f)
	{
		m_vForce.normalize(); //���� ����

		float m_fAccel = fForce / m_fMass; //���ӵ� ũ��(a = f/m)

		m_vAccel = m_vForce * m_fAccel; //���ӵ� ����

		m_vVelocity += m_vAccel * fDT; //�ӵ� -> ���ӵ� ��ŭ ����ؼ� ���ϸ�, ���ӵ� ��� ���� �ӵ��� ���� (V = a + dt)
	}

	//������ ������ �ݴ� ���������� ���ӵ�
	if (m_vVelocity.IsZero() != true) //���� ������ �ʾ����� �ӵ��� 0�� �ƴ� ��쿡 ����(�ڵ�� �ӵ� �Է�)
	{
		Vec2 vFricDir = m_vVelocity;
		Vec2 vFriction = -vFricDir.normalize() * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			//���� ���ӵ��� ������ Ŭ ��(�и��� ����)
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			//�� �ܿ���, �и�
			m_vVelocity += vFriction;
		}

		//�ִ� �ӵ��� �Ѿ�� �ӵ� ����
		if (m_vVelocity.Length() > m_fMaxSpeed)
		{
			m_vVelocity.normalize();
			m_vVelocity *= m_fMaxSpeed;
		}
	}

	Move();
	//���� ������ �ڿ��� ���� ���� 0���� ����� -> �̹� ���� �༭ �о�±⿡
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	//�ӵ� ���͸� �����Ѵٸ�, �Ʒ��� ���� 2���� ���� ����.
	//�ӷ�
	float fSpeed = m_vVelocity.Length();

	if (fSpeed != 0.f)
	{
		//����
		Vec2 vDir = m_vVelocity;
		vDir.normalize(); //���۷����� ������ �����ϱ⿡ �������� ����

		Vec2 vPos = m_pOwner->GetPos();

		//�ǻ�� - �ӵ� ���Ϳ� �����ð���ŭ ���� ���� ������Ʈ�� ��ġ�� ����
		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}
}
