#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	//��, ��, ��, �� �̵��� ���� ó�� -> ������Ʈ ��ǥ�� �ð��� * �̵��ӵ��� ���Ͽ� ��ġ�� �ű��.
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}

	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	//�̻��� �߻� ó�� -> �����̽��ٰ� ������, �̻��� ���� �Լ� ����
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

//�̻��� ���� �Լ�
void CPlayer::CreateMissile()
{
	//�̻��� ������Ʈ ��ü�� ����
	CMissile* pMissile = new CMissile;

	//�̻����� �߻��ϴ� ������Ʈ�� ��ġ(�÷��̾�) - �÷��̾� y�� ���� ���� = �̻����� �����Ǵ� ��ġ
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	//�̻��Ͽ� ���� �ʱ� ���� ����
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(true);

	//�� ��ü�� �����Ͽ�, ���Ŵ����� ���� ���� ���� �������� �� ���� �̻����� �߰��Ѵ�(�׸���)
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
