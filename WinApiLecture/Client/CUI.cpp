#include "CUI.h"
#include "CCamera.h"

CUI::CUI() : m_pParentUI(nullptr)
{
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

	//�׸��� �ڽ��� �ڽ� ������Ʈ�鿡��, �ڽ��� ��ġ �̵��� �˸��� �ڽĵ��� ��ġ�� ������� ��
	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc, 
		int(vPos.x),
		int(vPos.y),
		int(vPos.x + vScale.x),
		int(vPos.y + vScale.y));

	render_child(_dc);
}

