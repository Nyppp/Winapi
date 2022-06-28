#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"


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
