#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

//CCore* CCore::g_pInst = nullptr;
//CObject g_obj;

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	//윈도우와 그 해상도를 가져옴
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	//해상도에 맞게 현재 윈도우 크기 조정
	//50,50 위치에, 입력받은 해상도 크기 x,y 만큼의 크기를 가진 윈도우로 해상도 변경

	//LPRECT == RECT 포인터 타입
	RECT rc = {0, 0, m_ptResolution.x, m_ptResolution.y};

	//윈도우 크기를 지정한 해상도 사이즈가 나오게 조정해줌, rc를 수정하기에 const pointer로 받지 않음
	//메뉴바나, 좌우 여백을 신경써서 윈도우 크기를 보장해주기 때문에, 기존에 RECT 변수에 있던 해상도를 보장해준다.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hwnd, NULL, 100, 100, rc.right - rc.left, rc.bottom - rc.top, 0);
	
	//기존 직접 해상도를 입력하여 윈도우 크기를 설정하는것보다 정확하게 해상도를 보장해줌
	//SetWindowPos(m_hwnd, NULL, 100, 100, m_ptResolution.x, m_ptResolution.y, 0);

	//내부적으로 draw 할 공간을 가져오는 GetDC 함수(커널함수)
	//윈도우가 보유한 비트맵을 DC가 목적지로 삼는 것
	m_hDC = GetDC(m_hwnd);

	//이중 버퍼링 용도의 비트맵과 dc 생성
	//윈도우 화면의 픽셀 집합 -> 비트맵 으로 관리
	//윈도우와 똑같은 비트맵을 만듦, CompatibleBitmap은 현재 윈도우와 호환되는 윈도우라는 의미
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	//DC는 만들어질 때 기본적으로 1픽셀짜리 목적지가 포함되어있음(더미 데이터)
	//SelectObject는 펜, 브러쉬를 바꾸는 것 뿐 아니라 그림을 그리는 목적지도 변경가능
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);

	//현재 memDC는 1픽셀짜리 더미 데이터가 그림공간으로 있기에 바로 지워버림
	DeleteObject(hOldBit);

	//자주 사용하는 펜, 브러쉬 초기화
	CreateBrushPen();

	//Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
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
	CSceneMgr::GetInst()->update(); //씬 매니저를 통해 어떤 오브젝트가 어느 위치에 존재하는지 계산
	CCollisionMgr::GetInst()->update(); //그 후 씬에 담겨있는 오브젝트들의 충돌체를 업데이트
	

	//기존 Ccore에서 프레임 기준 업데이트 : Unity 엔진에서의 Update문과 비슷한 동작으로, 매 프레임마다 동작을 하게 된다.
	//문제점 : PC환경에 따라 연산 횟수가 다름
	//update(); -> 씬 매니저의 업데이트로 대체함

	
	//렌더링 -> 더블 버퍼링 사용해서 잔상 제거
	//이전 프레임에 그려진 장면을 모두 지움
	//화면 전체를 지우는 목적이기 때문에 -1부터 최대값 +1까지 지우기
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CSceneMgr::GetInst()->render(m_memDC); //렌더링은 씬 매니저를 통해 그려냄

	//한 DC에 담긴 비트맵을 다른 DC에 옮겨주는 BitBlt 함수
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	//여기까지가 게임의 아주 기본적인 틀
	//이제부터는 고급 렌더링이나, 3D 개념이 추가적으로 들어가는것 뿐임
}

void CCore::CreateBrushPen()
{
	//자체 설계를 위해 윈도우 함수에 의존하지 않고, 자체적으로 hollow brush 값을 받아둬서 사용
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	//RED펜
	m_arrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

CCore::CCore() 
	: m_hwnd(0), 
	m_ptResolution{}, 
	m_hDC(0), 
	m_hBit(0),
	m_memDC(0),
	m_arrBrush{},
	m_arrPen{}
{

}

CCore::~CCore()
{
	//init할 때 가져온 Device context를 해제함
	ReleaseDC(m_hwnd, m_hDC);

	//메인 윈도우와 연결되지 않은 DC는 비트맵과 각각 지워줘야 함
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}
