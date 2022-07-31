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

#include "AI.h"
#include "CState.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

CScene_Start::CScene_Start() : m_bUseForce(false), m_fForceRadius(300.f), m_fCurRadius(0.f), m_fForce(300.f)
{
}

CScene_Start::~CScene_Start()
{
}



void CScene_Start::Enter()
{

	//�÷��̾� ������Ʈ
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CCamera::GetInst()->SetTarget(pObj);

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//���� ������Ʈ �߰�
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//���丮 ������ Ȱ�� -> ��ü�� �̱���ó�� �������� �ʰ�, ���� �ٷ� �����ؼ� �Լ��� ��� -> ���� ����Լ��̱⿡ ��� ����
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, (vResolution / 2.f) - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	//Ÿ�� �ε�
	//LoadTile(L"Tile\\test.tile");

	//�浹 ����
	//�÷��̾� �׷�� ���� �׷� �� �浹üũ
	//�� �浹 ���� ������ �ش� ���� �����Ǵ� ���ȿ��� ������ �浹������
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//�⺻ ī�޶� ���� -> ��ü �ػ��� �� �߾� ��ġ
	CCamera::GetInst()->SetLookAt(vResolution/2.f);

	//�÷��̾ ����ٴϰ� ����
	CCamera::GetInst()->SetTarget(pObj);

	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
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
	//CScene::update();

	/*if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}*/

	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
		m_fCurRadius = 0.f;
	}

	//������ٵ� ������ ���� ��ŸƮ ������ ��ü������ ������Ʈ ������Ʈ
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);
		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (vecObj[j]->IsDead() == false)
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					//���콺 ��ǥ�� ������Ʈ ��ǥ ���̸� ���ϰ�,
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();

					//������Ʈ ��ǥ�� ���� ���� �ȿ� ������ ��,
					if (fLen < m_fForceRadius)
					{
						//���� �߽����κ��� �󸶳� ������ �ִ��� ������ ���ϰ�, �� ������ŭ ���� �ش�.
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						//���� ������ ������ ������ ������Ʈ�� ���� �����Ѵ�
						vecObj[j]->GetRigidBody()->AddForce(vDiff.normalize() * fForce);
					}
				}
				vecObj[j]->update();
			}
		}
	}
}

void CScene_Start::render(HDC _dc)
{
	//���� �� ������ ����
	CScene::render(_dc);

	//������ٵ� �ð������� ǥ���ϱ� ���� ����
	if (m_bUseForce == false)
	{
		return;
	}
	
	//��, �귯�� ������
	SelectGDI gdiBrush(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdiPen(_dc, PEN_TYPE::GREEN);

	//�������� �׸��µ�, ���콺 Ŭ�� �������� 1000.f�� �ѷ��� ���� ���� �� �� ���� ��������
	m_fCurRadius += m_fForceRadius * 3.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc, 
		(vRenderPos.x - m_fCurRadius),
		(vRenderPos.y - m_fCurRadius),
		(vRenderPos.x + m_fCurRadius),
		(vRenderPos.y + m_fCurRadius));

}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);


}

