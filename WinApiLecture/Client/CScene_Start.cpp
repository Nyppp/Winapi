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
	LoadTile(L"Tile\\test.tile");

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
	CScene::update();

	/*if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}*/
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}
