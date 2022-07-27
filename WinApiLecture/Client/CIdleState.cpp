#include "global.h"
#include "CIdleState.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CMonster.h"

//�θ� Ŭ������ ������Ʈ ���� �޾ƿ��� ������ �̿��ؼ�, �θ� Ŭ������ �ڽ��� � ������Ʈ���� �˷���
CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}


void CIdleState::update()
{
	//IDLE STATE -> ������ ������
	//�÷��̾��� ��ġ üũ, �÷��̾ ���� ���� ���� ������ ���� ���·� ��ȯ
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	//���� ��ü�� �����´�.
	CMonster* pMonster = GetMonster();
	Vec2 vMonsterPos = pMonster->GetPos();

	//�÷��̾�� ���� ������ �Ÿ��� ����
	Vec2 vDiff = vPlayerPos - vMonsterPos;
	float fLen = vDiff.Length();

	//�̺�Ʈ ��ȯ ����, �ٸ� update���� �̺�Ʈ ó���� ��ũ�� ���� Ư�� �ñ⿡ ó���ϱ� ������,
	//������Ʈ ������Ʈ�� �ƴ� ai�� ������Ʈ�� �̺�Ʈ ó���� �ٸ� �̺�Ʈ�� �ϰ������� �� ������ ���� ���� �̷������ �Ѵ�.
	if (fLen < pMonster->GetMonInfo().fRecogRange)
	{
		//�ν� ���� ���� �÷��̾ ������, �������·� AI ������Ʈ ����
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}
}


void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}
