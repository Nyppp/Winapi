#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject() : m_vPos{}, m_vScale{}
{
}

CObject::~CObject()
{
}

//������Ʈ�� �ڱ� �ڽ��� �׷���
void CObject::render(HDC _dc)
{
	m_vPos;
	m_vScale;

	Rectangle(_dc,
		(int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f),
		(int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));
}
