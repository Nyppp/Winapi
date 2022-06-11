#include "pch.h"
#include "CCore.h"

//CCore* CCore::g_pInst = nullptr;

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	//윈도우와 그 해상도를 가져옴
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	//해상도에 맞게 현재 윈도우 크기 조정
	//50,50 위치에, 입력받은 해상도 크기 x,y 만큼의 크기를 가진 윈도우로 해상도 변경
	SetWindowPos(m_hwnd, NULL, 50, 50, m_ptResolution.x, m_ptResolution.y, 0);
	return 0;
}

//메시지가 없을 때 코어 클래스에서 처리할 동작
void CCore::progress()
{

}

CCore::CCore()
{

}

CCore::~CCore()
{

}
