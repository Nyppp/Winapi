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
	//1�ʿ� �鸸�� ���� ������ �Լ�
	QueryPerformanceCounter(&m_llCurCount);

	//1�ʴ� ī��Ʈ�� �󸶳� �߻��ϴ��� ���� �Լ�
	QueryPerformanceCounter(&m_llFrequency);

}
