#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr() : m_vecEvent{}
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _Event)
{
	switch (_Event.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lparam : ������Ʈ �ּ�
		// wparam : ������Ʈ �׷� Ÿ��
		CObject* pNewObj = (CObject*)_Event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_Event.wParam;

		//������Ʈ�� �ּҿ� �׷�Ÿ���� �ް�, ���� ���� �߰��Ѵ�.
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);

	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:

		break;
	case EVENT_TYPE::SCENE_CHANGE:

		break;
	}
}
