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
	//드래그 시, UI가 마우스를 따라가게 한다. -> 우선 클릭이 된 채로 마우스가 ui위에 있어야 함
	if (isLbtnDown())
	{
		//클릭 시 좌표와 현재 좌표 차이를 구해서
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		//UI 위치에 더한다
		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		//드래그 시작점을 현재 마우스 위치로 갱신시켜준다. -> 안할 경우, 무한으로 움직임
		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	//패널 ui는 왼클릭이 된 시점의 좌표를 기억해둔다.
	m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}