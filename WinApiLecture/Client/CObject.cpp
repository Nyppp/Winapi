#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CObject::CObject() : m_vPos{}, m_vScale{}, m_pCollider(nullptr), m_bAlive(true), m_pAnimator(nullptr)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName),
	m_vPos(_origin.m_vPos),
	m_vScale(_origin.m_vScale),
	m_pCollider(nullptr), m_pAnimator(nullptr), m_bAlive(true)
{
	//������ ��ü�� �ݶ��̴��� ���� ��쿡�� �ݶ��̴� ���� ����
	//�ݶ��̴��� ��쿡��, �� ������Ʈ�� �� �ݶ��̴��� ���ÿ� ����Ű�� �Ǹ� ���� �߻���.(�ؽ��Ŀʹ� �ٸ� ���)
	if (_origin.m_pCollider != nullptr)
	{
		//�ݶ��̴��� �ݶ��̴��� ���� ������ ��������� ����� ����
		m_pCollider = new CCollider(*_origin.m_pCollider);
		//CreateCollider���� �����ϴ� Owner ������ ���ش�
		m_pCollider->m_pOwner = this;
	}
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

//������Ʈ�� �ڱ� �ڽ��� �׷���
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
