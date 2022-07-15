#include "CUI.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"

CUI::CUI(bool _bCamAff) : m_pParentUI(nullptr), m_bCameraAffected(_bCamAff), m_bMouseOn(false), m_bLbtnDown(false)
{
}

CUI::CUI(const CUI& _origin)
	//�ڽ� Ŭ������ ���� �����ڸ� ������ ��, �θ� Ŭ������ ���� ��������ڰ� �����Ѵٸ�,
	//�θ� Ŭ������ ���� �����ڸ� ����Ѵٰ� �ڽ� Ŭ������ ���� �����ڿ��� ������־�� �Ѵ�.
	: CObject(_origin),
	m_pParentUI(nullptr), m_bCameraAffected(_origin.m_bCameraAffected), m_bMouseOn(false), m_bLbtnDown(false)
{
	//UI�� �ڽ� ������Ʈ�� ���� ��� ���� ���縦 �Ѵ�.
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

//�ڽ� UI�鿡 ���� ������Ʈ, ������ ó��
void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::update()
{
	//update��������, �ڽ� ui���� ������Ʈ�� ����
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();

	m_vFinalPos = GetPos();

	//�׸��� finalupdate���� �ڽ��� ������ ��ġ�� ����
	if (GetParent())
	{
		//�θ� UI�� �����ϸ�, �θ� UI�� ��ġ + �ڽ��� ��ġ�� ����Ѵ�.
		//�θ� UI�� �������� ���������� ���.
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	//���콺 üũ
	MouseOnCheck();

	//�׸��� �ڽ��� �ڽ� ������Ʈ�鿡��, �ڽ��� ��ġ �̵��� �˸��� �ڽĵ��� ��ġ�� ������� ��
	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	//UI�� ī�޶� ������ ������, ������ ��ġ�� �޾ƿͼ� ��ġ ����
	if (m_bCameraAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	//UI�� ���� ���¶��, ���� ��������
	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		Rectangle(_dc,
			int(vPos.x),
			int(vPos.y),
			int(vPos.x + vScale.x),
			int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc,
			int(vPos.x),
			int(vPos.y),
			int(vPos.x + vScale.x),
			int(vPos.y + vScale.y));
	}

	//�ڽ��� �׸� ����, �ڽ�UI�� �׷�����.
	render_child(_dc);
}


void CUI::MouseOnCheck()
{
	//UI�� ��ġ�� ũ�⸦ �޴´�.
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	//ī�޶��� ������ �޴� UI���, ī�޶� ���� ��ǥ�� ��ȯ�����ش�.
	if (m_bCameraAffected)
	{
		vMousePos = CCamera::GetInst()->GetRenderPos(vMousePos);
	}

	//UI�� ��ġ �ȿ� ���콺�� �����ϸ� m_bMouseOn�� true�� �ȴ�.
	if (m_vFinalPos.x <= vMousePos.x && m_vFinalPos.x + vScale.x >= vMousePos.x &&
		m_vFinalPos.y <= vMousePos.y && m_vFinalPos.y + vScale.y >= vMousePos.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{

}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{

}

void CUI::MouseLbtnCliked()
{

}


