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
	//콜라이더 지정
	CreateCollider();
	//오프셋을 주면, 오프셋 만큼 콜라이더 중심 좌표가 변경됨
	GetCollider()->SetOffsetPos(Vec2(0.f, -20.f));
	GetCollider()->SetScale(Vec2(20.f, 50.f));

	CreateRigidBody();

	//텍스쳐 로딩
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Animation\\Link.bmp");

	CreateAnimator();
	//텍스쳐 정보를 애니메이션이 모두 알고있기에, 플레이어 클래스는 더이상 텍스쳐를 멤버로 가질 필요가 없음
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.3f, 3 , Vec2(0.f , -20.f));
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10, Vec2(0.f, -20.f));
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 390.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10, Vec2(0.f, -20.f));
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10, Vec2(0.f, -20.f));
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10, Vec2(0.f, -20.f));

	//두번째 인자로, 애니메이션 반복 여부를 입력받음 -> 상용엔진의 animation repeat 기능
	//GetAnimator()->Play(L"WALK_DOWN", true);
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	CRigidBody* pRigid = GetRigidBody();

	//상, 하, 좌, 우 이동에 대한 처리 -> 오브젝트 좌표에 시간값 * 이동속도를 더하여 위치를 옮긴다.
	if (KEY_HOLD(KEY::W))
	{
		//1. 트랜스폼을 사용한 오브젝트 이동
		//vPos.y -= 200.f * fDT;
		
		//2. 리지드바디를 사용한 오브젝트 이동
		pRigid->AddForce(Vec2(0.f, -200.f));

		//걷는 방향에 맞는 애니메이션 재생
		GetAnimator()->Play(L"WALK_UP", true);

		//미사일 발사 방향 지정
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

	//처음 누른 경우, 보정 속도로 초기 속도 100.f만큼의 값을 준다.
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

	//미사일 발사 처리 -> 스페이스바가 눌리면, 미사일 생성 함수 실행
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
	//컴포넌트(충돌체와 같은 추가적으로 오브젝트에 붙는 요소들) 렌더링
	//+ 애니메이션 렌더링
	component_render(_dc);

	//알파 블렌딩 실습
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Player", L"texture\\Player_A.bmp");

	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);

	//float Width = (float)pTex->Width();
	//float Height = (float)pTex->Height();

	////블렌딩 함수
	//BLENDFUNCTION bf = {};
	//
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 255;

	////32비트 비트맵 리소스에 대해서, 알파값을 참고하여 리소스를 그린다.
	//AlphaBlend(_dc, 
	//	vPos.x - Width / 2.f,
	//	vPos.y - Height /2.f,
	//	Width, Height,
	//	pTex->GetDC(),
	//	0, 0, Width, Height,
	//	bf);
}

//미사일 생성 함수
void CPlayer::CreateMissile()
{
	//미사일 오브젝트 객체를 생성
	CMissile* pMissile = new CMissile;

	//미사일을 발사하는 오브젝트의 위치(플레이어) - 플레이어 y축 넓이 절반 = 미사일이 생성되는 위치
	Vec2 vMissilePos = GetCollider()->GetFinalPos();

	//미사일에 대한 초기 정보 설정
	pMissile->SetPos(vMissilePos);
	pMissile->SetName(L"Missile_Player");
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(m_FireDir);

	//씬 객체를 생성하여, 씬매니저를 통해 현재 씬을 가져오고 그 씬에 미사일을 추가한다(그린다)
	//CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);

	//하지만 이 방법은, 동기화 되지 않은 상태로 실행되기에 논리적으로 오류가 발생할 수 있음
	//이벤트 관리자를 통해, 프레임 마다 동기화 된 함수를 기준으로 오브젝트를 생성해야 함
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

