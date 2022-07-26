#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CCollider.h"
#include "AI.h"

#include <random>

CMonster::CMonster() : m_fSpeed(100.f), m_iHP(5), m_pAI(nullptr)
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
	if (m_pAI != nullptr)
		delete m_pAI;
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::update()
{
	m_pAI->update();
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	//몬스터 오브젝트가 플레이어가 쏜 미사일에 맞으면 오브젝트 삭제
	//그러나 렌더링이나, 참조 타입 등의 문제로 바로 지우면 문제 발생
	//거기다, 씬 변경으로 오브젝트들이 바뀌면 업데이트는 이전 씬 기준인데, 렌더링은 바뀐 씬으로 하게 됨
	//오브젝트 삭제에 대한 일괄적 동작 필요 -> 이벤트를 이용

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		--m_iHP;

		if(m_iHP <= 0)
			DeleteObject(this);
	}
}
