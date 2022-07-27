#include "pch.h"
#include "func.h"
#include "CObject.h"

#include "CEventMgr.h"

//오브젝트 생성
void CreateObject(CObject* _pObj, GROUP_TYPE _eGROUP)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGROUP;

	CEventMgr::GetInst()->AddEvent(evn);
}

//오브젝트 삭제
void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(evn);
}

//씬 전환
void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeAIState(AI* _pAI, MON_STATE _eNextState)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_AISTATE;
	evn.lParam = (DWORD_PTR)_pAI;
	evn.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GetInst()->AddEvent(evn);
}
