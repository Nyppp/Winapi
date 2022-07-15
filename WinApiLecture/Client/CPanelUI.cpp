#include "CPanelUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI() : CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::update()
{

}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);
}

void CPanelUI::MouseOn()
{
	//�巡�� ��, UI�� ���콺�� ���󰡰� �Ѵ�. -> �켱 Ŭ���� �� ä�� ���콺�� ui���� �־�� ��
	if (isLbtnDown())
	{
		//Ŭ�� �� ��ǥ�� ���� ��ǥ ���̸� ���ؼ�
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		//UI ��ġ�� ���Ѵ�
		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		//�巡�� �������� ���� ���콺 ��ġ�� ���Ž����ش�. -> ���� ���, �������� ������
		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	//�г� ui�� ��Ŭ���� �� ������ ��ǥ�� ����صд�.
	m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}