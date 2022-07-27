#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"
#include "resource.h"

//CCore* CCore::g_pInst = nullptr;
//CObject g_obj;

CCore::CCore()
	: m_hwnd(0),
	m_ptResolution{},
	m_hDC(0),
	m_pMemTex(nullptr),
	m_arrBrush{},
	m_arrPen{}
{
}

CCore::~CCore()
{
	//init�� �� ������ Device context�� ������
	ReleaseDC(m_hwnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	//�޴� �� ����
	DestroyMenu(m_hMenu);
}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	//������� �� �ػ󵵸� ������
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;
		
	//������ ������ ����
	ChangeWindowSize(GetVecResolution(), false);

	//�޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	
	//���� ���� �ػ󵵸� �Է��Ͽ� ������ ũ�⸦ �����ϴ°ͺ��� ��Ȯ�ϰ� �ػ󵵸� ��������
	//SetWindowPos(m_hwnd, NULL, 100, 100, m_ptResolution.x, m_ptResolution.y, 0);

	//���������� draw �� ������ �������� GetDC �Լ�(Ŀ���Լ�)
	//�����찡 ������ ��Ʈ���� DC�� �������� ��� ��
	m_hDC = GetDC(m_hwnd);

	//���� ���۸� �뵵�� ��Ʈ�ʰ� dc ����
	//������ ȭ���� �ȼ� ���� -> ��Ʈ�� ���� ����
	//������� �Ȱ��� ��Ʈ���� ����, CompatibleBitmap�� ���� ������� ȣȯ�Ǵ� �������� �ǹ�

	//���� �ھ�� ���� dc�� ��Ʈ���� �����ϴ� ������ ���ҽ� �Ŵ����� �ϵ��� ����
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);


	//���� ����ϴ� ��, �귯�� �ʱ�ȭ
	CreateBrushPen();

	//Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
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
	CCamera::GetInst()->update(); //ī�޶� ������Ʈ
	
	
	//�� ������Ʈ
	CSceneMgr::GetInst()->update(); //�� �Ŵ����� ���� � ������Ʈ�� ��� ��ġ�� �����ϴ��� ���
	
	//�浹 üũ
	CCollisionMgr::GetInst()->update(); //�� �� ���� ����ִ� ������Ʈ���� �浹ü�� ������Ʈ

	//UI�̺�Ʈ üũ
	CUIMgr::GetInst()->update();
	

	//���� Ccore���� ������ ���� ������Ʈ : Unity ���������� Update���� ����� ��������, �� �����Ӹ��� ������ �ϰ� �ȴ�.
	//������ : PCȯ�濡 ���� ���� Ƚ���� �ٸ�
	//update(); -> �� �Ŵ����� ������Ʈ�� ��ü��

	
	//������ -> ���� ���۸� ����ؼ� �ܻ� ����
	//���� �����ӿ� �׷��� ����� ��� ����
	//ȭ�� ��ü�� ����� �����̱� ������ -1���� �ִ밪 +1���� �����
	
	Clear();

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC()); //�������� �� �Ŵ����� ���� �׷���
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	//�� DC�� ��� ��Ʈ���� �ٸ� DC�� �Ű��ִ� BitBlt �Լ�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();
	//������ �Ϸ�

	//�̺�Ʈ ���� ó��
	//�� �����ӿ��� ���� �̺�Ʈ�� �߻��� �� �ְ�, �̰��� ���� �����ӿ�
	//�ϰ������� ó����Ŵ -> ���� �����ӿ�ũ �� ���� ���߿� ó����
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	//������ ���������� ��ĥ -> �ھ� Ŭ������ progress �Լ��� �ְ� �Ǹ�,
	//GDI�� ���� �귯���� ���� ���� �ٽ� �⺻ �귯���� ��ȯ�ϴ� ������ progress �Լ��� ���� �� �����ϱ⿡, �ٸ� ������Ʈ���� �׷����� ����
	//�Լ��� ���� �����ؼ� SelectGDI�� �Ҹ��ڸ� ȣ���� �⺻ �귯��, ���� ���������� ����
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);

	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	//��ü ���踦 ���� ������ �Լ��� �������� �ʰ�, ��ü������ hollow brush ���� �޾Ƶּ� ���
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//RED��
	m_arrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

//�޴� �ٸ� �� �������� ��Ÿ���� ���� �Լ���
//�޴� �ٰ� ���� ���� ���� ���� ������ ����� �����ϴ� �Լ�
void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	//LPRECT == RECT ������ Ÿ��
	RECT rc = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	//������ ũ�⸦ ������ �ػ� ����� ������ ��������, rc�� �����ϱ⿡ const pointer�� ���� ����
	//�޴��ٳ�, �¿� ������ �Ű�Ἥ ������ ũ�⸦ �������ֱ� ������, ������ RECT ������ �ִ� �ػ󵵸� �������ش�.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hwnd, nullptr, 100, 100, rc.right - rc.left, rc.bottom - rc.top, 0);
}

//�޴� �� ��� �Լ�
void CCore::DockMenu()
{
	//�� ������ ����� �޴��� �ҷ��´�.
	SetMenu(m_hwnd, m_hMenu);
	ChangeWindowSize(GetVecResolution(), true);
}

//�޴� �� ���� �Լ�
void CCore::DivideMenu()
{
	SetMenu(m_hwnd, nullptr);
	ChangeWindowSize(GetVecResolution(), false);
}


