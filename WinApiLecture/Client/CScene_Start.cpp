#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"

void CScene_Start::Enter()
{

	//�÷��̾� ������Ʈ
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//���� ������Ʈ �߰�
	int iMonCount = 15;

	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//���� ������ ���� = (�ػ�x�� - (�̵��ִ�Ÿ� + (������Ʈũ�� ����)) *2) / ���� ����-1 -> �ֿܰ� ���� ���̵� ���Ͱ� �̵��ϴ� �ݰ��� ����, �� ������ ���Ͱ��� -1��ŭ ������.
	//���Ͱ� 2�������, ������ �Ǿհ� �ǵڷ� ũ��, �������� �۾�����.
	float fTerm = (vResolution.x - ((fMoveDist + (fObjScale / 2.f)) * 2)) / (float)(iMonCount-1);

	//���Ͱ� �Ѹ����� �� ����� �ȵ� -> 0���� ó��
	if (iMonCount == 1)
	{
		fTerm = 0.f;
	}

	CMonster* pMonsterObj = nullptr;

	for (int i = 0; i < iMonCount; ++i)
	{
		CMonster* pMonsterObj = new CMonster;
		//������ �߾� ��ǥ =  �̵��ݰ� + ����ũ�� ���� + ���� ���� ����*i
		pMonsterObj->SetCenterPos(Vec2((fMoveDist + fObjScale / 2.f) + (fTerm * (float)i), 50.f));

		//������ ��ǥ�� ���� ������Ʈ�� ����(������ �ϴ°��� ���� ������Ʈ�̱� ������)
		//������ ȣ�� ����
		//�� �Ŵ��� -> �� -> ���� �����ϴ� ������Ʈ �迭 �� ��ü -> ������Ʈ -> ������.
		pMonsterObj->SetPos(Vec2(pMonsterObj->GetCenterPos()));

		//�̵��ݰ�� ���� ũ�⸦ �������ְ�, ���� ������Ʈ �߰�
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	//�浹 ����
	//�÷��̾� �׷�� ���� �׷� �� �浹üũ
	//�� �浹 ���� ������ �ش� ���� �����Ǵ� ���ȿ��� ������ �浹������
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//�⺻ ī�޶� ���� -> ��ü �ػ��� �� �߾� ��ġ
	CCamera::GetInst()->SetLookAt(vResolution/2.f);
}

void CScene_Start::Exit()
{
	//���� ���� �� ��� ������Ʈ ����
	DeleteAll();

	//���� �ű� ��, �浹 ���踦 ��� �ʱ�ȭ��Ų��.
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}
