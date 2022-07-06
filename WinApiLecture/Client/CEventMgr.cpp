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
		// lparam : 오브젝트 주소
		// wparam : 오브젝트 그룹 타입
		CObject* pNewObj = (CObject*)_Event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_Event.wParam;

		//오브젝트의 주소와 그룹타입을 받고, 현재 씬에 추가한다.
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);

	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:

		break;
	case EVENT_TYPE::SCENE_CHANGE:

		break;
	}
}
