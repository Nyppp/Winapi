#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CCamera.h"

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

	//�ִϸ����͵� ���� ������� ����
	if (_origin.m_pAnimator != nullptr)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

CObject::~CObject()
{
	//�ݶ��̴��� �ִϸ������� �Ҹ��� �� �ݶ��̴�, �ִϸ������� �Ҹ��ڸ� ȣ���ϵ��� ��
	if (m_pCollider != nullptr)
		delete m_pCollider;

	if (m_pAnimator != nullptr)
		delete m_pAnimator;
}

void CObject::finalupdate()
{
	//������Ʈ ������ ������Ʈ(�̵�, ������)�� ��ġ��, �� �������� �ݶ��̴�, �ִϸ��̼� ó��
	if (m_pCollider)
		m_pCollider->finalupdate();

	if (m_pAnimator)
		m_pAnimator->finalupdate();
}

//������Ʈ�� �ڱ� �ڽ��� �׷���
void CObject::render(HDC _dc)
{

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_dc,
		(int)(vRenderPos.x - m_vScale.x / 2.f), (int)(vRenderPos.y - m_vScale.y / 2.f),
		(int)(vRenderPos.x + m_vScale.x / 2.f), (int)(vRenderPos.y + m_vScale.y / 2.f));

	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->render(_dc);
	}

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->render(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
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
