#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"

void CScene_Start::Enter()
{
	//�ؽ��� �ε�
	CTexture* pTex = new CTexture;

	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += L"texture\\Player.bmp";
	pTex->Load(strFilepath);

	delete pTex;

	//�÷��̾� ������Ʈ
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100, 100));
	AddObject(pObj, GROUP_TYPE::DEFAULT);

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
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}

}

void CScene_Start::Exit()
{

}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}
