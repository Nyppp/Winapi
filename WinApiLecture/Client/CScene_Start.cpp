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

	//플레이어 오브젝트
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CCamera::GetInst()->SetTarget(pObj);

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//몬스터 오브젝트 추가
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//팩토리 패턴의 활용 -> 객체를 싱글턴처럼 생성하지 않고, 직접 바로 접근해서 함수를 사용 -> 정적 멤버함수이기에 사용 가능
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, (vResolution / 2.f) - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);
	
	//타일 로딩
	//LoadTile(L"Tile\\test.tile");

	//충돌 지정
	//플레이어 그룹과 몬스터 그룹 간 충돌체크
	//이 충돌 관계 설정은 해당 씬이 유지되는 동안에만 설정된 충돌관계임
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//기본 카메라 세팅 -> 전체 해상도의 정 중앙 위치
	CCamera::GetInst()->SetLookAt(vResolution/2.f);

	//플레이어를 따라다니게 설정
	CCamera::GetInst()->SetTarget(pObj);

	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}

void CScene_Start::Exit()
{
	//씬을 나갈 때 모든 오브젝트 삭제
	DeleteAll();

	//씬을 옮길 때, 충돌 관계를 모두 초기화시킨다.
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

	//리지드바디 동작을 위해 스타트 씬에서 자체적으로 오브젝트 업데이트
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);
		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (vecObj[j]->IsDead() == false)
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					//마우스 좌표와 오브젝트 좌표 차이를 구하고,
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();

					//오브젝트 좌표가 힘의 범위 안에 존재할 때,
					if (fLen < m_fForceRadius)
					{
						//힘의 중심으로부터 얼마나 떨어져 있는지 비율을 구하고, 그 비율만큼 힘을 준다.
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						//힘의 비율과 방향을 가지고 오브젝트에 힘을 전달한다
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
	//기존 씬 렌더링 동작
	CScene::render(_dc);

	//리지드바디를 시각적으로 표현하기 위한 동작
	if (m_bUseForce == false)
	{
		return;
	}
	
	//펜, 브러쉬 가져옴
	SelectGDI gdiBrush(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdiPen(_dc, PEN_TYPE::GREEN);

	//원형으로 그리는데, 마우스 클릭 지점부터 1000.f의 둘레를 가진 원이 될 때 까지 퍼져나감
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

