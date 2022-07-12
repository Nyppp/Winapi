#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"


CCamera::CCamera()
	: m_pTargetObj(nullptr), m_fTime(1.f), m_fSpeed(0.f), m_fAccTime(1.f)
{

}

CCamera::~CCamera()
{

}


//������Ʈ�� ��� ����ٴϰ� ��
void CCamera::update()
{
	if (m_pTargetObj != nullptr)
	{
		//deadó���� ������Ʈ���, �Ҵ� ����
		if (m_pTargetObj->IsDead() == true)
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			SetLookAt(m_pTargetObj->GetPos());
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_vLookAt.y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_vLookAt.y += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_vLookAt.x -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_vLookAt.x += 500.f * fDT;
	}

	//ȭ�� �߾���ǥ�� ī�޶� LookAt��ǥ�� ���� �� ���
	CalDiff();
}

//ȭ�� �߾Ӱ��� ī�޶� ��ǥ�� ���� ����ϴ� �Լ�
void CCamera::CalDiff()
{
	//�ð����ѿ� ���� ��� ī�޶� �̵�
	m_fAccTime += fDT;

	if (m_fAccTime > m_fTime)
	{
	m_vCurLookAt = m_vLookAt;
	}
	else
	{
	//ī�޶� ��ġ�� �ٲ���� ��, �̵��ؾ� �� ����

		//m_vLookAt -> ��ǥ ��ǥ / m_vPrevLookAt ���� ��ǥ
		Vec2 vLookDir = (m_vLookAt - m_vPrevLookAt);

		m_vCurLookAt = m_vPrevLookAt + vLookDir.normalize() * m_fSpeed * fDT;
	}

	//�ε巯�� ī�޶� �̵�
	/*float fMoveDist = (m_vLookAt - m_vCurLookAt).Length();

	if (m_fSpeed < 10.f)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{

		Vec2 vLookDir = (m_vLookAt - m_vPrevLookAt);

		m_vCurLookAt = m_vPrevLookAt + vLookDir.normalize() * m_fSpeed * fDT * 2.f;

		m_fSpeed = (fMoveDist / (m_fTime));
		
	}*/

	//���� LookAt�� ���� LookAt�� ���̸� �����ؼ� ���� LookAt�� ���
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 Center = vResolution / 2.f;

	//ī�޶� ��ġ ����
	m_vDiff = m_vCurLookAt - Center;
	m_vPrevLookAt = m_vCurLookAt;
}
