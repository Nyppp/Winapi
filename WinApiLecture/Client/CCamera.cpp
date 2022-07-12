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


//오브젝트를 계속 따라다니게 함
void CCamera::update()
{
	if (m_pTargetObj != nullptr)
	{
		//dead처리된 오브젝트라면, 할당 해제
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

	//화면 중앙좌표와 카메라 LookAt좌표의 차이 값 계산
	CalDiff();
}

//화면 중앙값과 카메라 좌표의 차를 계산하는 함수
void CCamera::CalDiff()
{
	//시간제한에 따른 등속 카메라 이동
	m_fAccTime += fDT;

	if (m_fAccTime > m_fTime)
	{
	m_vCurLookAt = m_vLookAt;
	}
	else
	{
	//카메라 위치가 바뀌었을 때, 이동해야 할 방향

		//m_vLookAt -> 목표 좌표 / m_vPrevLookAt 현재 좌표
		Vec2 vLookDir = (m_vLookAt - m_vPrevLookAt);

		m_vCurLookAt = m_vPrevLookAt + vLookDir.normalize() * m_fSpeed * fDT;
	}

	//부드러운 카메라 이동
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

	//이전 LookAt과 현재 LookAt의 차이를 보정해서 현재 LookAt을 계산
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 Center = vResolution / 2.f;

	//카메라 위치 보정
	m_vDiff = m_vCurLookAt - Center;
	m_vPrevLookAt = m_vCurLookAt;
}
