#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CCamera.h"

CMissile::CMissile() : m_fTheta(PI/2.f), m_vDir(Vec2(1.f,1.f))
{
	//���� ����ȭ
	m_vDir.normalize();

	CreateCollider();

	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	//�ﰢ�Լ��� �̿��� ���� ���
	//cos -> x��ǥ / sin -> y��ǥ -> �ﰢ�Լ��� �������� ����Ѵ�. -> ������ ������ ������ �̵����� ���� �ΰ��� �ʿ��ϱ⿡ ������ �� ����
	//�̸� �ذ��ϱ� ���� -> �̵������ �Ÿ��� ��� ����ִ� 'Vector' ���� ���
	//vPos.x += 200.f * fDT * cosf(m_fTheta);
	//vPos.y -= 200.f * fDT * sinf(m_fTheta);

	//���͸� ����ȭ �߱⿡, ������ x������ cos, y������ sin�� ���Ѵ�.
	vPos.x += 600.f * fDT * m_vDir.x; 
	vPos.y += 600.f * fDT * m_vDir.y;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	Ellipse(_dc,
		(int)(vRenderPos.x - vScale.x / 2.f), (int)(vRenderPos.y - vScale.y / 2.f),
		(int)(vRenderPos.x + vScale.x / 2.f), (int)(vRenderPos.y + vScale.y / 2.f));

	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}


