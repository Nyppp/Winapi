#include "pch.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr()
	:m_llCurCount{}
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//1초에 백만을 세는 윈도우 함수
	QueryPerformanceCounter(&m_llCurCount);

	//1초당 카운트가 얼마나 발생하는지 세는 함수
	QueryPerformanceCounter(&m_llFrequency);

}
