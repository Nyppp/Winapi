#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

void CScene_Start::Enter()
{

	//�÷��̾� ������Ʈ
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//���� ������Ʈ �߰�
	int iMonCount = 5;

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
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	//�浹 ����
	//�÷��̾� �׷�� ���� �׷� �� �浹üũ
	//�� �浹 ���� ������ �ش� ���� �����Ǵ� ���ȿ��� ������ �浹������
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

}

void CScene_Start::Exit()
{
	//���� �ű� ��, �浹 ���踦 ��� �ʱ�ȭ��Ų��.
	CCollisionMgr::GetInst()->Reset();
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}
