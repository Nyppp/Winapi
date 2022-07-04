#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

//CCore* CCore::g_pInst = nullptr;
//CObject g_obj;

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

	//���� ����ϴ� ��, �귯�� �ʱ�ȭ
	CreateBrushPen();

	//Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	
	return S_OK;
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

	//�Ŵ��� ������Ʈ -> �ð� ��� ������Ʈ -> fixedupdate�� ������
	CTimeMgr::GetInst()->update(); //�ð����� �����ͼ� �����ӱ��� �ð��� ��������
	CKeyMgr::GetInst()->update(); //Ű �Ŵ����� ���� � Ű�� ���ȴ��� üũ�ϰ�
	CSceneMgr::GetInst()->update(); //�� �Ŵ����� ���� � ������Ʈ�� ��� ��ġ�� �����ϴ��� ���
	CCollisionMgr::GetInst()->update(); //�� �� ���� ����ִ� ������Ʈ���� �浹ü�� ������Ʈ
	

	//���� Ccore���� ������ ���� ������Ʈ : Unity ���������� Update���� ����� ��������, �� �����Ӹ��� ������ �ϰ� �ȴ�.
	//������ : PCȯ�濡 ���� ���� Ƚ���� �ٸ�
	//update(); -> �� �Ŵ����� ������Ʈ�� ��ü��

	
	//������ -> ���� ���۸� ����ؼ� �ܻ� ����
	//���� �����ӿ� �׷��� ����� ��� ����
	//ȭ�� ��ü�� ����� �����̱� ������ -1���� �ִ밪 +1���� �����
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CSceneMgr::GetInst()->render(m_memDC); //�������� �� �Ŵ����� ���� �׷���

	//�� DC�� ��� ��Ʈ���� �ٸ� DC�� �Ű��ִ� BitBlt �Լ�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	//��������� ������ ���� �⺻���� Ʋ
	//�������ʹ� ��� �������̳�, 3D ������ �߰������� ���°� ����
}

void CCore::CreateBrushPen()
{
	//��ü ���踦 ���� ������ �Լ��� �������� �ʰ�, ��ü������ hollow brush ���� �޾Ƶּ� ���
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	//RED��
	m_arrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

CCore::CCore() 
	: m_hwnd(0), 
	m_ptResolution{}, 
	m_hDC(0), 
	m_hBit(0),
	m_memDC(0),
	m_arrBrush{},
	m_arrPen{}
{

}

CCore::~CCore()
{
	//init�� �� ������ Device context�� ������
	ReleaseDC(m_hwnd, m_hDC);

	//���� ������� ������� ���� DC�� ��Ʈ�ʰ� ���� ������� ��
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}
