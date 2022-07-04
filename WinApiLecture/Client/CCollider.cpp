#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

//콜라이더가 생성될 때 마다, nextid가 증가함 -> 콜라이더 갯수를 알아낼 수 있음
CCollider::CCollider() : m_pOwner(nullptr), m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	Vec2 vObjectPos = m_pOwner->GetPos();

	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	//콜라이더를 렌더링 하는 방법
	//1. 오브젝트의 테두리만 그리는 방법 -> 사실상 실제 게임에선 사용불가능

	//2. Rect를 그린 다음, 내부에 오브젝트를 그려넣음(공백을 둠)
	//그러나 오브젝트의 종류마다 콜라이더 표시 색을 다르게 하면, 펜을 여러번 꺼내 쓰고 지우는 반복작업이 들어감

	//render 함수가 끝날 때, SelectGDI객체는 임시 객체이기 때문에 소멸자 호출
	SelectGDI p(_dc, PEN_TYPE::GREEN);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc,
		(int)(m_vFinalPos.x - m_vScale.x / 2.f),
		(int)(m_vFinalPos.y - m_vScale.y / 2.f),
		(int)(m_vFinalPos.x + m_vScale.x / 2.f),
		(int)(m_vFinalPos.y + m_vScale.y / 2.f));
}
