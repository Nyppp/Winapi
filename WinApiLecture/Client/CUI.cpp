#include "CUI.h"
#include "CCamera.h"

CUI::CUI() : m_pParentUI(nullptr)
{
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

//자식 UI들에 대한 업데이트, 렌더링 처리
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
	//update문에서는, 자식 ui들의 업데이트를 진행
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();

	m_vFinalPos = GetPos();

	//그리고 finalupdate에서 자신의 최종적 위치를 결정
	if (GetParent())
	{
		//부모 UI가 존재하면, 부모 UI의 위치 + 자신의 위치를 계산한다.
		//부모 UI의 포지션을 오프셋으로 취급.
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	//그리고 자신의 자식 오브젝트들에게, 자신의 위치 이동을 알리고 자식들이 위치를 따라오게 함
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

