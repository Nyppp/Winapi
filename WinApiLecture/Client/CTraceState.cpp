#include "global.h"
#include "CTraceState.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

void CTraceState::update()
{
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonPos = GetMonster()->GetPos();

	//플레이어와 몬스터 사이 거리 계산
	Vec2 vMonDir = vPlayerPos - vMonPos;
	if (vMonDir.Length() > GetMonster()->GetMonInfo().fRecogRange)
	{
		//만약 인식범위보다 플레이어가 멀리 있다면 유휴 상태로 전환
		ChangeAIState(GetAI(), MON_STATE::IDLE);
	}

	//플레이어와 몬스터 벡터의 방향 벡터
	vMonDir.normalize();

	//몬스터 위치를 플레이어 방향으로 이동시킨다.
	vMonPos += vMonDir * GetMonster()->GetMonInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);
}
