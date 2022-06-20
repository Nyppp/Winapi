#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

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

	//Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	

	Vec2 vPos = Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2));
	Vec2 vSacle = Vec2(100, 100);
	g_obj.SetPos(vPos);
	g_obj.SetScale(vSacle);

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
	//static int Callcount = 0;
	//++Callcount;

	//static int iPrevCount = GetTickCount64();

	//int iCurCount = GetTickCount64();
	//if (iCurCount - iPrevCount > 1000)
	//{
	//	//���� ó������ �ʰ� �׳� �׸��⸦ �ϸ�, 1�ʿ� �� 3~4���� �׸��� �� -> ��ü�� ������ ��ΰ� �ܻ����� ���ԵǴ� ���� �߻�
	//	Callcount;
	//	iPrevCount = iCurCount;
	//	Callcount = 0;
	//}

	//Unity ���������� Update���� ����� ��������, �� �����Ӹ��� ������ �ϰ� �ȴ�.
	//������ : PCȯ�濡 ���� ���� Ƚ���� �ٸ�
	update();

	render();

}

//��ü���� ��ǥ �������� ������Ʈ �ϴ� �Լ�
void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	//GetAsyncKeyState -> �޽��� ���ο� �������, �Ű������� �� Ű�� ���� �������� ��ȯ
	//��ҿ��� � ���°����� �־�������, 0x8000�� ��Ʈ�����ڸ� �ϸ� ����, �ȴ��� ���θ��� �˾Ƴ� �� ����
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

//��ü���� �׸��� �Լ�
void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	//�ᱹ, ���� �� ��ü�� ��ǥ�� ����� �������ָ� �װ��� �׸��� ��
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
	//init�� �� ������ Device context�� ������
	ReleaseDC(m_hwnd, m_hDC);
}
