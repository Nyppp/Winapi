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
	RECT rc = {0, 0, m_ptResolution.x, m_ptResolution.y};

	//������ ũ�⸦ ������ �ػ� ����� ������ ��������, rc�� �����ϱ⿡ const pointer�� ���� ����
	//�޴��ٳ�, �¿� ������ �Ű�Ἥ ������ ũ�⸦ �������ֱ� ������, ������ RECT ������ �ִ� �ػ󵵸� �������ش�.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hwnd, NULL, 100, 100, rc.right - rc.left, rc.bottom - rc.top, 0);
	
	//���� ���� �ػ󵵸� �Է��Ͽ� ������ ũ�⸦ �����ϴ°ͺ��� ��Ȯ�ϰ� �ػ󵵸� ��������
	//SetWindowPos(m_hwnd, NULL, 100, 100, m_ptResolution.x, m_ptResolution.y, 0);

	//���������� draw �� ������ �������� GetDC �Լ�(Ŀ���Լ�)
	//�����찡 ������ ��Ʈ���� DC�� �������� ��� ��
	m_hDC = GetDC(m_hwnd);

	//���� ���۸� �뵵�� ��Ʈ�ʰ� dc ����
	//������ ȭ���� �ȼ� ���� -> ��Ʈ�� ���� ����
	//������� �Ȱ��� ��Ʈ���� ����, CompatibleBitmap�� ���� ������� ȣȯ�Ǵ� �������� �ǹ�
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	//DC�� ������� �� �⺻������ 1�ȼ�¥�� �������� ���ԵǾ�����(���� ������)
	//SelectObject�� ��, �귯���� �ٲٴ� �� �� �ƴ϶� �׸��� �׸��� �������� ���氡��
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);

	//���� memDC�� 1�ȼ�¥�� ���� �����Ͱ� �׸��������� �ֱ⿡ �ٷ� ��������
	DeleteObject(hOldBit);

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

	//�Ŵ��� ������Ʈ -> �ð� ��� ������Ʈ
	CTimeMgr::GetInst()->update();

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
		//�������� �۾��� �þ���� �Ҿ����ϱ� ������,
		//�������� �ð����� Ȱ���ؼ� �̵����� ��ȭ��Ŵ
		vPos.x -= 200.f * fDT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 200.f * fDT;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		vPos.y -= 200.f * fDT;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		vPos.y += 200.f * fDT;
	}

	g_obj.SetPos(vPos);
}

//��ü���� �׸��� �Լ�
void CCore::render()
{
	//���� �����ӿ� �׷��� ����� ��� ����
	//ȭ�� ��ü�� ����� �����̱� ������ -1���� �ִ밪 +1���� �����
	Rectangle(m_memDC, -1, -1, m_ptResolution.x+1, m_ptResolution.y+1 );

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	//�ᱹ, ���� �� ��ü�� ��ǥ�� ����� �������ָ� �װ��� �׸��� ��
	Rectangle(m_memDC, 
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

	//�� DC�� ��� ��Ʈ���� �ٸ� DC�� �Ű��ִ� BitBlt �Լ�
	BitBlt(m_hDC, 0,0, m_ptResolution.x, m_ptResolution.y, 
		m_memDC, 0,0, SRCCOPY);
}

CCore::CCore() 
	: m_hwnd(0), 
	m_ptResolution{}, 
	m_hDC(0), 
	m_hBit(0),
	m_memDC(0)
{

}

CCore::~CCore()
{
	//init�� �� ������ Device context�� ������
	ReleaseDC(m_hwnd, m_hDC);

	//���� ������� ������� ���� DC�� ��Ʈ�ʰ� ���� ������� ��
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}
