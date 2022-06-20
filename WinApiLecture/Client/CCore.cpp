#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

//CCore* CCore::g_pInst = nullptr;

CObject g_obj;

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	//윈도우와 그 해상도를 가져옴
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	//해상도에 맞게 현재 윈도우 크기 조정
	//50,50 위치에, 입력받은 해상도 크기 x,y 만큼의 크기를 가진 윈도우로 해상도 변경

	//LPRECT == RECT 포인터 타입
	RECT rc = {0,0,m_ptResolution.x, m_ptResolution.y};

	//윈도우 크기를 지정한 해상도 사이즈가 나오게 조정해줌, rc를 수정하기에 const pointer로 받지 않음
	//메뉴바나, 좌우 여백을 신경써서 윈도우 크기를 보장해주기 때문에, 기존에 RECT 변수에 있던 해상도를 보장해준다.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, true);

	//기존 직접 해상도를 입력하여 윈도우 크기를 설정하는것보다 정확하게 해상도를 보장해줌
	//SetWindowPos(m_hwnd, NULL, 100, 100, rc.right - rc.left, rc.bottom - rc.top, 0);
	//SetWindowPos(m_hwnd, NULL, 100, 100, m_ptResolution.x, m_ptResolution.y, 0);

	//내부적으로 draw 할 공간을 가져오는 GetDC 함수(커널함수)
	m_hDC = GetDC(m_hwnd);

	//Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	

	Vec2 vPos = Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2));
	Vec2 vSacle = Vec2(100, 100);
	g_obj.SetPos(vPos);
	g_obj.SetScale(vSacle);

	//m_hDC에다가 Paint를 하면 이는, 메시지에 엮여있지 않게 윈도우에 그림을 그리는 동작임
	return 0;
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

	//Unity 엔진에서의 Update문과 비슷한 동작으로, 매 프레임마다 동작을 하게 된다.
	//문제점 : PC환경에 따라 연산 횟수가 다름
	update();

	render();

}

//물체들의 좌표 변경점을 업데이트 하는 함수
void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	//GetAsyncKeyState -> 메시지 여부에 관계없이, 매개변수로 들어간 키가 눌린 상태인지 반환
	//평소에는 어떤 상태값으로 주어지지만, 0x8000과 비트연산자를 하면 눌림, 안눌림 여부만을 알아낼 수 있음
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 0.01f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 0.01f;
	}

	g_obj.SetPos(vPos);
}

//물체들을 그리는 함수
void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	//결국, 게임 속 물체의 좌표만 제대로 갱신해주면 그것을 그리면 됨
	Rectangle(m_hDC, 
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

}

CCore::CCore() : m_hwnd(0), m_ptResolution{}, m_hDC(0)
{

}

CCore::~CCore()
{
	//init할 때 가져온 Device context를 해제함
	ReleaseDC(m_hwnd, m_hDC);
}
