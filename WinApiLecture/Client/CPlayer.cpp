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

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	//무조건 복사
	//BitBlt(_dc,
	//	int(vPos.x - (float)(iWidth / 2)),
	//	int(vPos.y - (float)(iHeight / 2)),
	//	iWidth, iHeight,
	//	m_pTex->GetDC(), 
	//	0, 0, SRCCOPY);

	//특정 조건을 걸어서, 해당 픽셀은 복사하지 않음 기능이 추가된 함수
	TransparentBlt(_dc, 
		int(vPos.x - (float)(iWidth / 2)),
		int(vPos.y - (float)(iHeight / 2)), 
		iWidth, iHeight, 
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight, RGB(255,255,255));

	//그러나 텍스쳐는 리소스를 불러오는 것 -> 여러 클래스가 동시에 접근하거나 생성하면 문제 발생
	//리소스 관리자를 통해 싱글턴 객체로 관리해야 함.
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
	pMissile->SetDir(Vec2(0.f, 1.f));

	//씬 객체를 생성하여, 씬매니저를 통해 현재 씬을 가져오고 그 씬에 미사일을 추가한다(그린다)
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

CPlayer::CPlayer() : m_pTex(nullptr)
{
	//텍스쳐 로딩
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");
	CreateCollider();
}

CPlayer::~CPlayer()
{

}
