#include "global.h"
#include "CIdleState.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CMonster.h"

//부모 클래스의 스테이트 값을 받아오는 생성자 이용해서, 부모 클래스에 자신이 어떤 스테이트인지 알려줌
CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}


void CIdleState::update()
{
	//IDLE STATE -> 가만히 정지함
	//플레이어의 위치 체크, 플레이어가 추적 범위 내로 들어오면 추적 상태로 전환
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	//몬스터 객체를 가져온다.
	CMonster* pMonster = GetMonster();
	Vec2 vMonsterPos = pMonster->GetPos();

	//플레이어와 몬스터 사이의 거리를 측정
	Vec2 vDiff = vPlayerPos - vMonsterPos;
	float fLen = vDiff.Length();

	//이벤트 전환 또한, 다른 update들이 이벤트 처리로 싱크를 맞춰 특정 시기에 처리하기 떄문에,
	//컴포넌트 업데이트가 아닌 ai의 업데이트도 이벤트 처리로 다른 이벤트와 일괄적으로 한 프레임 동작 이후 이루어져야 한다.
	if (fLen < pMonster->GetMonInfo().fRecogRange)
	{
		//인식 범위 내에 플레이어가 들어오면, 추적상태로 AI 스테이트 변경
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}
}


void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}
