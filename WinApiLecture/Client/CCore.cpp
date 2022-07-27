#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"
#include "resource.h"

//CCore* CCore::g_pInst = nullptr;
//CObject g_obj;

CCore::CCore()
	: m_hwnd(0),
	m_ptResolution{},
	m_hDC(0),
	m_pMemTex(nullptr),
	m_arrBrush{},
	m_arrPen{}
{
}

CCore::~CCore()
{
	//init할 때 가져온 Device context를 해제함
	ReleaseDC(m_hwnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	//메뉴 바 제거
	DestroyMenu(m_hMenu);
}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	//윈도우와 그 해상도를 가져옴
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;
		
	//윈도우 사이즈 설정
	ChangeWindowSize(GetVecResolution(), false);

	//메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	
	//기존 직접 해상도를 입력하여 윈도우 크기를 설정하는것보다 정확하게 해상도를 보장해줌
	//SetWindowPos(m_hwnd, NULL, 100, 100, m_ptResolution.x, m_ptResolution.y, 0);

	//내부적으로 draw 할 공간을 가져오는 GetDC 함수(커널함수)
	//윈도우가 보유한 비트맵을 DC가 목적지로 삼는 것
	m_hDC = GetDC(m_hwnd);

	//이중 버퍼링 용도의 비트맵과 dc 생성
	//윈도우 화면의 픽셀 집합 -> 비트맵 으로 관리
	//윈도우와 똑같은 비트맵을 만듦, CompatibleBitmap은 현재 윈도우와 호환되는 윈도우라는 의미

	//기존 코어에서 직접 dc와 비트맵을 생성하던 동작을 리소스 매니저가 하도록 변경
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);


	//자주 사용하는 펜, 브러쉬 초기화
	CreateBrushPen();

	//Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();
	
	return S_OK;
}


//메시지가 없을 때 코어 클래스에서 처리할 동작
void CCore::progress()
{
	//화면 그리기(메시지 처리를 하지 않을때도 그려져야 하기 때문에)
	//그러나 무작정 그리면, 메시지 없을 때 매 프레임마다 덧그리기를 하게 될 것임 -> 그러나 변경점이 있을 때 마다 그리기는 비효율적
	//왜냐하면 게임에서는, 변경점이 항상 존재하기에(배경 물체의 흔들림 - 나뭇잎, 바람 등)
	//게임 속 렌더링 -> 매 순간마다, 모든 장면을 지우고 다시 그리는 방법 사용
	//static int Callcount = 0;
	//++Callcount;

	//static int iPrevCount = GetTickCount64();

	//int iCurCount = GetTickCount64();
	//if (iCurCount - iPrevCount > 1000)
	//{
	//	//따로 처리하지 않고 그냥 그리기를 하면, 1초에 약 3~4만번 그리게 됨 -> 물체가 움직인 경로가 잔상으로 남게되는 문제 발생
	//	Callcount;
	//	iPrevCount = iCurCount;
	//	Callcount = 0;
	//}

	//매니저 업데이트 -> 시간 기반 업데이트 -> fixedupdate와 유사함
	CTimeMgr::GetInst()->update(); //시간값을 가져와서 프레임기준 시간을 가져오고
	CKeyMgr::GetInst()->update(); //키 매니저를 통해 어떤 키가 눌렸는지 체크하고
	CCamera::GetInst()->update(); //카메라 업데이트
	
	
	//씬 업데이트
	CSceneMgr::GetInst()->update(); //씬 매니저를 통해 어떤 오브젝트가 어느 위치에 존재하는지 계산
	
	//충돌 체크
	CCollisionMgr::GetInst()->update(); //그 후 씬에 담겨있는 오브젝트들의 충돌체를 업데이트

	//UI이벤트 체크
	CUIMgr::GetInst()->update();
	

	//기존 Ccore에서 프레임 기준 업데이트 : Unity 엔진에서의 Update문과 비슷한 동작으로, 매 프레임마다 동작을 하게 된다.
	//문제점 : PC환경에 따라 연산 횟수가 다름
	//update(); -> 씬 매니저의 업데이트로 대체함

	
	//렌더링 -> 더블 버퍼링 사용해서 잔상 제거
	//이전 프레임에 그려진 장면을 모두 지움
	//화면 전체를 지우는 목적이기 때문에 -1부터 최대값 +1까지 지우기
	
	Clear();

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC()); //렌더링은 씬 매니저를 통해 그려냄
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	//한 DC에 담긴 비트맵을 다른 DC에 옮겨주는 BitBlt 함수
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();
	//렌더링 완료

	//이벤트 지연 처리
	//한 프레임에서 여러 이벤트가 발생할 수 있고, 이것은 다음 프레임에
	//일괄적으로 처리시킴 -> 게임 프레임워크 중 가장 나중에 처리됨
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	//바탕을 검은색으로 색칠 -> 코어 클래스의 progress 함수에 넣게 되면,
	//GDI가 검은 브러쉬를 선택 이후 다시 기본 브러쉬로 반환하는 과정이 progress 함수가 끝날 때 동작하기에, 다른 오브젝트들이 그려지지 않음
	//함수로 따로 선언해서 SelectGDI가 소멸자를 호출해 기본 브러쉬, 펜을 가져오도록 설계
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);

	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	//자체 설계를 위해 윈도우 함수에 의존하지 않고, 자체적으로 hollow brush 값을 받아둬서 사용
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//RED펜
	m_arrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

//메뉴 바를 툴 씬에서만 나타내기 위한 함수들
//메뉴 바가 있을 때와 없을 때의 윈도우 사이즈를 보정하는 함수
void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	//LPRECT == RECT 포인터 타입
	RECT rc = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	//윈도우 크기를 지정한 해상도 사이즈가 나오게 조정해줌, rc를 수정하기에 const pointer로 받지 않음
	//메뉴바나, 좌우 여백을 신경써서 윈도우 크기를 보장해주기 때문에, 기존에 RECT 변수에 있던 해상도를 보장해준다.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hwnd, nullptr, 100, 100, rc.right - rc.left, rc.bottom - rc.top, 0);
}

//메뉴 바 출력 함수
void CCore::DockMenu()
{
	//툴 씬에서 사용할 메뉴를 불러온다.
	SetMenu(m_hwnd, m_hMenu);
	ChangeWindowSize(GetVecResolution(), true);
}

//메뉴 바 숨김 함수
void CCore::DivideMenu()
{
	SetMenu(m_hwnd, nullptr);
	ChangeWindowSize(GetVecResolution(), false);
}


