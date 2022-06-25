#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	//상, 하, 좌, 우 이동에 대한 처리 -> 오브젝트 좌표에 시간값 * 이동속도를 더하여 위치를 옮긴다.
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

	//미사일 발사 처리 -> 스페이스바가 눌리면, 미사일 생성 함수 실행
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

//미사일 생성 함수
void CPlayer::CreateMissile()
{
	//미사일 오브젝트 객체를 생성
	CMissile* pMissile = new CMissile;

	//미사일을 발사하는 오브젝트의 위치(플레이어) - 플레이어 y축 넓이 절반 = 미사일이 생성되는 위치
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	//미사일에 대한 초기 정보 설정
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(true);

	//씬 객체를 생성하여, 씬매니저를 통해 현재 씬을 가져오고 그 씬에 미사일을 추가한다(그린다)
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
