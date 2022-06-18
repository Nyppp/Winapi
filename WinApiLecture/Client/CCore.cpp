#include "pch.h"
#include "CCore.h"
#include "CObject.h"

//CCore* CCore::g_pInst = nullptr;

CObject g_obj;

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	//������� �� �ػ󵵸� ������
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	//�ػ󵵿� �°� ���� ������ ũ�� ����
	//50,50 ��ġ��, �Է¹��� �ػ� ũ�� x,y ��ŭ�� ũ�⸦ ���� ������� �ػ� ����

	//LPRECT == RECT ������ Ÿ��
	RECT rc = {0,0,m_ptResolution.x, m_ptResolution.y};

	//������ ũ�⸦ ������ �ػ� ����� ������ ��������, rc�� �����ϱ⿡ const pointer�� ���� ����
	//�޴��ٳ�, �¿� ������ �Ű�Ἥ ������ ũ�⸦ �������ֱ� ������, ������ RECT ������ �ִ� �ػ󵵸� �������ش�.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, true);

	//���� ���� �ػ󵵸� �Է��Ͽ� ������ ũ�⸦ �����ϴ°ͺ��� ��Ȯ�ϰ� �ػ󵵸� ��������
	//SetWindowPos(m_hwnd, NULL, 100, 100, rc.right - rc.left, rc.bottom - rc.top, 0);
	//SetWindowPos(m_hwnd, NULL, 100, 100, m_ptResolution.x, m_ptResolution.y, 0);

	//���������� draw �� ������ �������� GetDC �Լ�(Ŀ���Լ�)
	m_hDC = GetDC(m_hwnd);

	g_obj.m_ptPos = POINT{ m_ptResolution.x/2 , m_ptResolution.y/2 };
	g_obj.m_ptScale = POINT{ 100, 100 };

	//m_hDC���ٰ� Paint�� �ϸ� �̴�, �޽����� �������� �ʰ� �����쿡 �׸��� �׸��� ������
	return 0;
}


//�޽����� ���� �� �ھ� Ŭ�������� ó���� ����
void CCore::progress()
{
	//ȭ�� �׸���(�޽��� ó���� ���� �������� �׷����� �ϱ� ������)
	//�׷��� ������ �׸���, �޽��� ���� �� �� �����Ӹ��� ���׸��⸦ �ϰ� �� ���� -> �׷��� �������� ���� �� ���� �׸���� ��ȿ����
	//�ֳ��ϸ� ���ӿ�����, �������� �׻� �����ϱ⿡(��� ��ü�� ��鸲 - ������, �ٶ� ��)
	//���� �� ������ -> �� ��������, ��� ����� ����� �ٽ� �׸��� ��� ���
	static int Callcount = 0;
	++Callcount;

	static int iPrevCount = GetTickCount64();

	int iCurCount = GetTickCount64();
	if (iCurCount - iPrevCount > 1000)
	{
		//���� ó������ �ʰ� �׳� �׸��⸦ �ϸ�, 1�ʿ� �� 3~4���� �׸��� �� -> ��ü�� ������ ��ΰ� �ܻ����� ���ԵǴ� ���� �߻�
		Callcount;
		iPrevCount = iCurCount;
		Callcount = 0;
	}

	update();

	render();

}

//��ü���� ��ǥ �������� ������Ʈ �ϴ� �Լ�
void CCore::update()
{
	//GetAsyncKeyState -> �޽��� ���ο� �������, �Ű������� �� Ű�� ���� �������� ��ȯ
	//��ҿ��� � ���°����� �־�������, 0x8000�� ��Ʈ�����ڸ� �ϸ� ����, �ȴ��� ���θ��� �˾Ƴ� �� ����
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
	
}

//��ü���� �׸��� �Լ�
void CCore::render()
{
	//�ᱹ, ���� �� ��ü�� ��ǥ�� ����� �������ָ� �װ��� �׸��� ��
	Rectangle(m_hDC, 
		g_obj.m_ptPos.x - g_obj.m_ptScale.x/2,
		g_obj.m_ptPos.y - g_obj.m_ptScale.y/2, 
		g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2, 
		g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}

CCore::CCore() : m_hwnd(0), m_ptResolution{}, m_hDC(0)
{

}

CCore::~CCore()
{
	//init�� �� ������ Device context�� ������
	ReleaseDC(m_hwnd, m_hDC);
}
