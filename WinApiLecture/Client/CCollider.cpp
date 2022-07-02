#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

CCollider::CCollider() : m_pOwner(nullptr)
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
	//�ݶ��̴��� ������ �ϴ� ���
	//1. ������Ʈ�� �׵θ��� �׸��� ��� -> ��ǻ� ���� ���ӿ��� ���Ұ���

	//2. Rect�� �׸� ����, ���ο� ������Ʈ�� �׷�����(������ ��)
	//�׷��� ������Ʈ�� �������� �ݶ��̴� ǥ�� ���� �ٸ��� �ϸ�, ���� ������ ���� ���� ����� �ݺ��۾��� ��

	//render �Լ��� ���� ��, SelectGDI��ü�� �ӽ� ��ü�̱� ������ �Ҹ��� ȣ��
	SelectGDI p(_dc, PEN_TYPE::BLUE);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc,
		(int)(m_vFinalPos.x - m_vScale.x / 2.f),
		(int)(m_vFinalPos.y - m_vScale.y / 2.f),
		(int)(m_vFinalPos.x + m_vScale.x / 2.f),
		(int)(m_vFinalPos.y + m_vScale.y / 2.f));
}
