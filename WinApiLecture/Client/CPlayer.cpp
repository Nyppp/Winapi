#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

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

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	//������Ʈ(�浹ü�� ���� �߰������� ������Ʈ�� �ٴ� ��ҵ�) ������
	//+ �ִϸ��̼� ������
	component_render(_dc);
}

//�̻��� ���� �Լ�
void CPlayer::CreateMissile()
{
	//�̻��� ������Ʈ ��ü�� ����
	CMissile* pMissile = new CMissile;

	//�̻����� �߻��ϴ� ������Ʈ�� ��ġ(�÷��̾�) - �÷��̾� y�� ���� ���� = �̻����� �����Ǵ� ��ġ
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= (GetScale().y / 2.f);

	//�̻��Ͽ� ���� �ʱ� ���� ����
	pMissile->SetPos(vMissilePos);
	pMissile->SetName(L"Missile_Player");
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	//�� ��ü�� �����Ͽ�, ���Ŵ����� ���� ���� ���� �������� �� ���� �̻����� �߰��Ѵ�(�׸���)
	//CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);

	//������ �� �����, ����ȭ ���� ���� ���·� ����Ǳ⿡ �������� ������ �߻��� �� ����
	//�̺�Ʈ �����ڸ� ����, ������ ���� ����ȭ �� �Լ��� �������� ������Ʈ�� �����ؾ� ��
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

CPlayer::CPlayer()
{
	CreateCollider();
	
	//�������� �ָ�, ������ ��ŭ �ݶ��̴� �߽� ��ǥ�� �����
	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(20.f, 50.f));

	//�ؽ��� �ε�
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link0.bmp");
	CreateAnimator();
	//�ؽ��� ������ �ִϸ��̼��� ��� �˰��ֱ⿡, �÷��̾� Ŭ������ ���̻� �ؽ��ĸ� ����� ���� �ʿ䰡 ����
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f,260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);

	//�ι�° ���ڷ�, �ִϸ��̼� �ݺ� ���θ� �Է¹��� -> ��뿣���� animation repeat ���
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	//�ִϸ��̼� ������ -> �� ������Ʈ�� �ٸ� ��ġ�� �ִϸ��̼��� ������ �� �� ����
	for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
}

CPlayer::~CPlayer()
{

}
