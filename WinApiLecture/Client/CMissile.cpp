#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CCamera.h"

CMissile::CMissile() : m_fTheta(PI/2.f), m_vDir(Vec2(1.f,1.f))
{
	//벡터 정규화
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

	//삼각함수를 이용해 방향 계산
	//cos -> x좌표 / sin -> y좌표 -> 삼각함수는 라디안으로 계산한다. -> 하지만 각도의 계산법은 이동값과 방향 두개가 필요하기에 복잡할 수 있음
	//이를 해결하기 위해 -> 이동방향과 거리가 모두 담겨있는 'Vector' 개념 사용
	//vPos.x += 200.f * fDT * cosf(m_fTheta);
	//vPos.y -= 200.f * fDT * sinf(m_fTheta);

	//벡터를 정규화 했기에, 벡터의 x성분은 cos, y성분은 sin을 뜻한다.
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


