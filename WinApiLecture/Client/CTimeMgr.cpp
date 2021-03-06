#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

//유니온은 이렇게 선언해도 크기가 4바이트로 할당됨 -> 구조체는 8바이트
//제일 큰 사이즈 멤버를 기준으로, 전 멤버가 같은 메모리 공간을 사용하도록 설계됨
//TEST 유니온을 a로 접근하면, 거기 저장된 비트를 int로 해석하고, f로 접근하면 float로 해석함
//union TEST
//{
//	int a;
//	char f;
//};

CTimeMgr::CTimeMgr()
	:m_llCurCount{}
	, m_llFrequency{}
	, m_llPrevCount{}
	, m_dDT(0)
	, m_dACC(0)
	, m_iCallCount(0)
	, m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	//초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);

}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//이전 프레임의 카운트와 현재 프레임의 카운트 차이를 구함
	//update문은 1프레임마다 수행되기에, 두 count의 프레임 차이는 항상 1임
	//한 프레임 사이 카운트를 1초당 프레임 카운트로 나누면, 프레임 사이 시간을 구할수 있음
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	//위의 결과를 역수를 취하면, 초당 몇 프레임을 움직이는 지 알수 있음
	//그러나 프레임은 고정된 수치가 아니고, 매우 작은 값이기에 FPS가 고정적이지 못함

	//시간값 구한 후, 다음 프레임도 계산하기 위해 이전시간값을 현재 시간값으로 변경
	m_llPrevCount = m_llCurCount;

	//디버그 모드 전용 코드
#ifdef _DEBUG
	//디버그 모드에서는 60프레임으로 고정
	if (m_dDT > (1. / 60.))
	{
		m_dDT = (1. / 60.);
	}
#endif // _DEBUG

}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dACC += m_dDT; //DeltaTime 누적

	if (m_dACC >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dACC = 0;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
