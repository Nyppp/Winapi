#include "pch.h"
#include "CCore.h"

//CCore* CCore::g_pInst = nullptr;

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	//������� �� �ػ󵵸� ������
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	//�ػ󵵿� �°� ���� ������ ũ�� ����
	//50,50 ��ġ��, �Է¹��� �ػ� ũ�� x,y ��ŭ�� ũ�⸦ ���� ������� �ػ� ����
	SetWindowPos(m_hwnd, NULL, 50, 50, m_ptResolution.x, m_ptResolution.y, 0);
	return 0;
}

//�޽����� ���� �� �ھ� Ŭ�������� ó���� ����
void CCore::progress()
{

}

CCore::CCore()
{

}

CCore::~CCore()
{

}
