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

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	//������ ����
	//BitBlt(_dc,
	//	int(vPos.x - (float)(iWidth / 2)),
	//	int(vPos.y - (float)(iHeight / 2)),
	//	iWidth, iHeight,
	//	m_pTex->GetDC(), 
	//	0, 0, SRCCOPY);

	//Ư�� ������ �ɾ, �ش� �ȼ��� �������� ���� ����� �߰��� �Լ�
	TransparentBlt(_dc, 
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)), 
		iWidth, iHeight, 
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight, RGB(255,255,255));

	//�׷��� �ؽ��Ĵ� ���ҽ��� �ҷ����� �� -> ���� Ŭ������ ���ÿ� �����ϰų� �����ϸ� ���� �߻�
	//���ҽ� �����ڸ� ���� �̱��� ��ü�� �����ؾ� ��.
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
	pMissile->SetDir(Vec2(0.f, 1.f));

	//�� ��ü�� �����Ͽ�, ���Ŵ����� ���� ���� ���� �������� �� ���� �̻����� �߰��Ѵ�(�׸���)
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

CPlayer::CPlayer() : m_pTex(nullptr)
{
	//�ؽ��� �ε�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");
	CreateCollider();
}

CPlayer::~CPlayer()
{

}
