#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUIMgr.h"
#include "AI.h"
#include "CState.h"

CEventMgr::CEventMgr() : m_vecEvent{}, m_vecDeadObj{}
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{

	//���� ���� ������Ʈ ���� ó��
	for (size_t i = 0; i < m_vecDeadObj.size(); ++i)
	{
		delete m_vecDeadObj[i];
	}
	m_vecDeadObj.clear();

	//�̺�Ʈ ó��
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
	//������Ʈ ���� �̺�Ʈ
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

	//������Ʈ ���� �̺�Ʈ
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lparam : ������Ʈ �ּ�
		// wparam : ������

		//������Ʈ�� dead ���·� ���� -> ���� ���� ������Ʈ���� ��Ƶ�
		CObject* pDeadObj = (CObject*)_Event.lParam;

		pDeadObj->SetDead();

		m_vecDeadObj.push_back(pDeadObj);
		//���⿡�� ���� ���� ������Ʈ���� ���� ������ �������� �νĵ�
	}
		break;

	//�� ��ȯ �̺�Ʈ
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lparam : ���� �� Ÿ�� ��
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_Event.lParam);
		// �� ���� -> ��Ŀ�� �� UI�� ������Ų��.
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
		break;

	//AI ���� ��ȯ �̺�Ʈ
	case EVENT_TYPE::CHANGE_AISTATE:
	{
		// lparam : AI
		// wparam : ���� AI ����(��ȯ�� ����)
		AI* pAI = (AI*)_Event.lParam;
		MON_STATE eNextState = (MON_STATE)_Event.wParam;

		pAI->ChangeState(eNextState);
	}
	break;
	}
}
