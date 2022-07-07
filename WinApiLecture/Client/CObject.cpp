#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CObject::CObject() : m_vPos{}, m_vScale{}, m_pCollider(nullptr), m_bAlive(true)
{
}

CObject::~CObject()
{
	if (m_pCollider != nullptr)
		delete m_pCollider;
}

void CObject::finalupdate()
{
	if (m_pCollider)
		m_pCollider->finalupdate();
}

//오브젝트가 자기 자신을 그려냄
void CObject::render(HDC _dc)
{
	m_vPos;
	m_vScale;

	Rectangle(_dc,
		(int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f),
		(int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));

	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->render(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::OnCollision(CCollider* _pOther)
{
}

void CObject::OnCollisionEnter(CCollider* _pOther)
{
}

void CObject::OnCollisionExit(CCollider* _pOther)
{
}
