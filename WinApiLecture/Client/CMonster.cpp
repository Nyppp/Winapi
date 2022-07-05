#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CCollider.h"

#include <random>

CMonster::CMonster() : m_fSpeed(100.f), m_vCenterPos(Vec2(0.f, 0.f)), m_fMaxDistance(50.f), m_iDir(1), m_fCurTime(0.f), m_fRandomTime(0.f)
{
	//// 시드값을 얻기 위한 random_device 생성.
	//std::random_device rd;

	//std::default_random_engine gen(rd());

	//// 0.5초 ~1초 사이의 랜덤 값 부여
	//std::uniform_real_distribution<> dis(0.5f, 1.0f);

	//m_fRandomTime = dis(gen);

	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
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

	/* 과제 : 몬스터 미사일 발사 코드 작성 -> <random>헤더 사용하여 무작위 시간마다 미사일을 발사하게 코드 작성 */
	//시간값을 계속 증가시킨다.
	//m_fCurTime += fDT;

	////랜덤으로 부여된 미사일 발사 시간까지 도달하면, 미사일 발사
	//if (m_fCurTime >= m_fRandomTime)
	//{
	//	m_fCurTime = 0;
	//	//CreateMonsterMissile();
	//	
	//	//그 후 미사일 발사 시간도 다시 랜덤하게 지정(0.5초 ~ 1초 사이의 랜덤 값)
	//	std::random_device rd;
	//	std::default_random_engine gen(rd());
	//	std::uniform_real_distribution<> dis(0.5f, 1.0f);

	//	m_fRandomTime = dis(gen);
	//}
	
	SetPos(vCurPos);
}

//미사일 발사를 몬스터의 기준으로 발사
void CMonster::CreateMonsterMissile()
{
	//미사일 오브젝트 객체를 생성
	CMissile* pMissile = new CMissile;

	//미사일을 발사하는 오브젝트의 위치(플레이어) - 플레이어 y축 넓이 절반 = 미사일이 생성되는 위치
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	//미사일에 대한 초기 정보 설정
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f,-1.f));

	//씬 객체를 생성하여, 씬매니저를 통해 현재 씬을 가져오고 그 씬에 미사일을 추가한다(그린다)
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
