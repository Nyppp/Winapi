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
	//복사한 객체가 콜라이더가 있을 경우에만 콜라이더 깊은 복사
	//콜라이더의 경우에는, 두 오브젝트가 한 콜라이더를 동시에 가리키게 되면 문제 발생함.(텍스쳐와는 다른 경우)
	if (_origin.m_pCollider != nullptr)
	{
		//콜라이더는 콜라이더에 따로 선언한 복사생성자 사용해 대입
		m_pCollider = new CCollider(*_origin.m_pCollider);
		//CreateCollider에서 수행하던 Owner 지정도 해준다
		m_pCollider->m_pOwner = this;
	}

	//애니메이터도 같은 방법으로 적용
	if (_origin.m_pAnimator != nullptr)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

CObject::~CObject()
{
	//콜라이더와 애니메이터의 소멸은 각 콜라이더, 애니메이터의 소멸자를 호출하도록 함
	if (m_pCollider != nullptr)
		delete m_pCollider;

	if (m_pAnimator != nullptr)
		delete m_pAnimator;
}

void CObject::finalupdate()
{
	//오브젝트 단위의 업데이트(이동, 렌더링)을 마치면, 그 다음에는 콜라이더, 애니메이션 처리
	if (m_pCollider)
		m_pCollider->finalupdate();

	if (m_pAnimator)
		m_pAnimator->finalupdate();
}

//오브젝트가 자기 자신을 그려냄
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
