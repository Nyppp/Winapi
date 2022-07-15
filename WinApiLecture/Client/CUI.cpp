#include "CUI.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"

CUI::CUI(bool _bCamAff) : m_pParentUI(nullptr), m_bCameraAffected(_bCamAff), m_bMouseOn(false), m_bLbtnDown(false)
{
}

CUI::CUI(const CUI& _origin)
	//자식 클래스의 복사 생성자를 선언할 때, 부모 클래스도 깊은 복사생성자가 존재한다면,
	//부모 클래스의 복사 생성자를 사용한다고 자식 클래스의 복사 생성자에서 명시해주어야 한다.
	: CObject(_origin),
	m_pParentUI(nullptr), m_bCameraAffected(_origin.m_bCameraAffected), m_bMouseOn(false), m_bLbtnDown(false)
{
	//UI의 자식 오브젝트들 까지 모두 깊은 복사를 한다.
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
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

	//마우스 체크
	MouseOnCheck();

	//그리고 자신의 자식 오브젝트들에게, 자신의 위치 이동을 알리고 자식들이 위치를 따라오게 함
	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	//UI가 카메라 영향을 받으면, 렌더링 위치를 받아와서 위치 갱신
	if (m_bCameraAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	//UI가 눌린 상태라면, 색을 변경해줌
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

	//자신을 그린 다음, 자식UI를 그려낸다.
	render_child(_dc);
}


void CUI::MouseOnCheck()
{
	//UI의 위치와 크기를 받는다.
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	//카메라의 영향을 받는 UI라면, 카메라 기준 좌표로 변환시켜준다.
	if (m_bCameraAffected)
	{
		vMousePos = CCamera::GetInst()->GetRenderPos(vMousePos);
	}

	//UI의 위치 안에 마우스가 존재하면 m_bMouseOn은 true가 된다.
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


