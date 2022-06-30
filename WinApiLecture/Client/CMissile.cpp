#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"

CMissile::CMissile() : m_fTheta(PI/2.f), m_vDir(Vec2(1.f,1.f))
{
	//���� ����ȭ
	m_vDir.normalize();
	CreateCollider();
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
	vPos.y -= 600.f * fDT * m_vDir.y;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc,
		(int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}
