#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CMonster::CMonster() : m_fSpeed(100.f), m_vCenterPos(Vec2(0.f, 0.f)), m_fMaxDistance(50.f), m_iDir(1)
{
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	//이동 방향으로, 이동속도만큼 시간에 비례하여 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir;
	
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	//이동반경을 벗어나면, 방향 전환
	if (0.f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}