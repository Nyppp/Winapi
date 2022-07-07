#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr() : m_vecEvent{}, m_vecDeadObj{}
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{

	//삭제 예정 오브젝트 삭제 처리
	for (size_t i = 0; i < m_vecDeadObj.size(); ++i)
	{
		delete m_vecDeadObj[i];
	}
	m_vecDeadObj.clear();

	//이벤트 처리
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
	{
		// lparam : 오브젝트 주소
		// wparam : 사용안함

		//오브젝트를 dead 상태로 변경 -> 삭제 예정 오브젝트들을 모아둠
		CObject* pDeadObj = (CObject*)_Event.lParam;

		pDeadObj->SetDead();

		m_vecDeadObj.push_back(pDeadObj);
		//여기에서 쌓인 죽은 오브젝트들은 다음 프레임 기준으로 인식됨
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:

		break;
	}
}
