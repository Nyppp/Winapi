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

	//플레이어 오브젝트
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//몬스터 오브젝트 추가
	int iMonCount = 15;

	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//몬스터 사이의 간격 = (해상도x축 - (이동최대거리 + (오브젝트크기 절반)) *2) / 몬스터 갯수-1 -> 최외곽 양쪽 사이드 몬스터가 이동하는 반경을 빼고, 그 공간을 몬스터갯수 -1만큼 나눈다.
	//몬스터가 2마리라면, 간격은 맨앞과 맨뒤로 크고, 많을수록 작아진다.
	float fTerm = (vResolution.x - ((fMoveDist + (fObjScale / 2.f)) * 2)) / (float)(iMonCount-1);

	//몬스터가 한마리면 텀 계산이 안됨 -> 0으로 처리
	if (iMonCount == 1)
	{
		fTerm = 0.f;
	}

	CMonster* pMonsterObj = nullptr;

	for (int i = 0; i < iMonCount; ++i)
	{
		CMonster* pMonsterObj = new CMonster;
		//몬스터의 중앙 좌표 =  이동반경 + 몬스터크기 절반 + 몬스터 사이 간격*i
		pMonsterObj->SetCenterPos(Vec2((fMoveDist + fObjScale / 2.f) + (fTerm * (float)i), 50.f));

		//몬스터의 좌표를 몬스터 오브젝트에 전달(렌더링 하는것은 몬스터 오브젝트이기 떄문에)
		//렌더링 호출 순서
		//씬 매니저 -> 씬 -> 씬에 존재하는 오브젝트 배열 각 객체 -> 오브젝트 -> 렌더링.
		pMonsterObj->SetPos(Vec2(pMonsterObj->GetCenterPos()));

		//이동반경과 몬스터 크기를 설정해주고, 씬에 오브젝트 추가
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	//충돌 지정
	//플레이어 그룹과 몬스터 그룹 간 충돌체크
	//이 충돌 관계 설정은 해당 씬이 유지되는 동안에만 설정된 충돌관계임
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//기본 카메라 세팅 -> 전체 해상도의 정 중앙 위치
	CCamera::GetInst()->SetLookAt(vResolution/2.f);
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
