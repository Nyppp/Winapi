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
#include "CRigidBody.h"

CPlayer::CPlayer() : m_FireDir(0.f, -1.f)
{
	//�ݶ��̴� ����
	CreateCollider();
	//�������� �ָ�, ������ ��ŭ �ݶ��̴� �߽� ��ǥ�� �����
	GetCollider()->SetOffsetPos(Vec2(0.f, -20.f));
	GetCollider()->SetScale(Vec2(20.f, 50.f));

	CreateRigidBody();

	//�ؽ��� �ε�
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Animation\\Link.bmp");

	CreateAnimator();
	//�ؽ��� ������ �ִϸ��̼��� ��� �˰��ֱ⿡, �÷��̾� Ŭ������ ���̻� �ؽ��ĸ� ����� ���� �ʿ䰡 ����
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.3f, 3 , Vec2(0.f , -20.f));
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10, Vec2(0.f, -20.f));
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 390.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10, Vec2(0.f, -20.f));
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10, Vec2(0.f, -20.f));
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10, Vec2(0.f, -20.f));

	//�ι�° ���ڷ�, �ִϸ��̼� �ݺ� ���θ� �Է¹��� -> ��뿣���� animation repeat ���
	//GetAnimator()->Play(L"WALK_DOWN", true);
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	CRigidBody* pRigid = GetRigidBody();

	//��, ��, ��, �� �̵��� ���� ó�� -> ������Ʈ ��ǥ�� �ð��� * �̵��ӵ��� ���Ͽ� ��ġ�� �ű��.
	if (KEY_HOLD(KEY::W))
	{
		//1. Ʈ�������� ����� ������Ʈ �̵�
		//vPos.y -= 200.f * fDT;
		
		//2. ������ٵ� ����� ������Ʈ �̵�
		pRigid->AddForce(Vec2(0.f, -200.f));

		//�ȴ� ���⿡ �´� �ִϸ��̼� ���
		GetAnimator()->Play(L"WALK_UP", true);

		//�̻��� �߻� ���� ����
		m_FireDir.x = 0.f;
		m_FireDir.y = -1.f;
	}

	if (KEY_HOLD(KEY::S))
	{
		//vPos.y += 200.f * fDT;
		pRigid->AddForce(Vec2(0.f, 200.f));
		GetAnimator()->Play(L"WALK_DOWN", true);

		m_FireDir.x = 0.f;
		m_FireDir.y = 1.f;
	}

	if (KEY_HOLD(KEY::A))
	{
		//vPos.x -= 200.f * fDT;
		pRigid->AddForce(Vec2(-200.f, 0.f));
		GetAnimator()->Play(L"WALK_LEFT", true);

		m_FireDir.x = -1.f;
		m_FireDir.y = 0.f;
	}

	if (KEY_HOLD(KEY::D))
	{
		//vPos.x += 200.f * fDT;
		pRigid->AddForce(Vec2(200.f, 0.f));
		GetAnimator()->Play(L"WALK_RIGHT", true);

		m_FireDir.x = 1.f;
		m_FireDir.y = 0.f;
	}

	//ó�� ���� ���, ���� �ӵ��� �ʱ� �ӵ� 100.f��ŭ�� ���� �ش�.
	if (KEY_TAP(KEY::W))
	{
		pRigid->AddForce(Vec2(0.f, -100.f));
	}
	if (KEY_TAP(KEY::S))
	{
		pRigid->AddForce(Vec2(0.f, 100.f));
	}
	if (KEY_TAP(KEY::A))
	{
		pRigid->AddForce(Vec2(-100.f, 0.f));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->AddForce(Vec2(100.f, 0.f));
	}

	//�̻��� �߻� ó�� -> �����̽��ٰ� ������, �̻��� ���� �Լ� ����
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	if (KEY_NONE(KEY::A) && KEY_NONE(KEY::W) && KEY_NONE(KEY::S) && KEY_NONE(KEY::D))
	{
		GetAnimator()->Play(L"IDLE", true);
	}


	//SetPos(vPos);

	//GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	//������Ʈ(�浹ü�� ���� �߰������� ������Ʈ�� �ٴ� ��ҵ�) ������
	//+ �ִϸ��̼� ������
	component_render(_dc);

	//���� ���� �ǽ�
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Player", L"texture\\Player_A.bmp");

	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);

	//float Width = (float)pTex->Width();
	//float Height = (float)pTex->Height();

	////���� �Լ�
	//BLENDFUNCTION bf = {};
	//
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 255;

	////32��Ʈ ��Ʈ�� ���ҽ��� ���ؼ�, ���İ��� �����Ͽ� ���ҽ��� �׸���.
	//AlphaBlend(_dc, 
	//	vPos.x - Width / 2.f,
	//	vPos.y - Height /2.f,
	//	Width, Height,
	//	pTex->GetDC(),
	//	0, 0, Width, Height,
	//	bf);
}

//�̻��� ���� �Լ�
void CPlayer::CreateMissile()
{
	//�̻��� ������Ʈ ��ü�� ����
	CMissile* pMissile = new CMissile;

	//�̻����� �߻��ϴ� ������Ʈ�� ��ġ(�÷��̾�) - �÷��̾� y�� ���� ���� = �̻����� �����Ǵ� ��ġ
	Vec2 vMissilePos = GetCollider()->GetFinalPos();

	//�̻��Ͽ� ���� �ʱ� ���� ����
	pMissile->SetPos(vMissilePos);
	pMissile->SetName(L"Missile_Player");
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(m_FireDir);

	//�� ��ü�� �����Ͽ�, ���Ŵ����� ���� ���� ���� �������� �� ���� �̻����� �߰��Ѵ�(�׸���)
	//CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);

	//������ �� �����, ����ȭ ���� ���� ���·� ����Ǳ⿡ �������� ������ �߻��� �� ����
	//�̺�Ʈ �����ڸ� ����, ������ ���� ����ȭ �� �Լ��� �������� ������Ʈ�� �����ؾ� ��
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

