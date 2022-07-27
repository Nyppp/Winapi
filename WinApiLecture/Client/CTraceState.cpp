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

	//�÷��̾�� ���� ���� �Ÿ� ���
	Vec2 vMonDir = vPlayerPos - vMonPos;
	if (vMonDir.Length() > GetMonster()->GetMonInfo().fRecogRange)
	{
		//���� �νĹ������� �÷��̾ �ָ� �ִٸ� ���� ���·� ��ȯ
		ChangeAIState(GetAI(), MON_STATE::IDLE);
	}

	//�÷��̾�� ���� ������ ���� ����
	vMonDir.normalize();

	//���� ��ġ�� �÷��̾� �������� �̵���Ų��.
	vMonPos += vMonDir * GetMonster()->GetMonInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);
}
