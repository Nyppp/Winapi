#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CUI.h"

CUIMgr::CUIMgr() : m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI 확인
	// 기존 포커스를 유지해야 하는지, 새로운 포커스 된 ui가 있는지 판단
	m_pFocusedUI = GetFocusedUI();

	// 2. 포커스 된 ui 내에서, 자식 ui들 중 타겟인 ui를 가져온다.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (pTargetUI != nullptr)
	{
		pTargetUI->MouseOn();

		//왼클릭이 됐다면 LbtnDown 이벤트 호출
		if (bLbtnTap == true)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}

		//해당 UI 위에서 왼클릭 해제 시 -> LbtnUp 이벤트 호출
		else if (bLbtnAway == true)
		{
			pTargetUI->MouseLbtnUp();

			//UI가 눌려있는 상태에서 떼는 이벤트 둘다 발생 -> 클릭 이벤트를 호출한다.
			if (pTargetUI->m_bLbtnDown == true)
			{
				pTargetUI->MouseLbtnCliked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
	}
	
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	//버튼이 떼져있는지 여부
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	//부모UI 포함, 모든 자식들을 검사(BFS알고리즘 사용)
	static list<CUI*> queue;

	//타겟 ui가 아닌 것들을 모은 벡터
	static vector<CUI*> vecNoneTarget;

	//함수에 지역변수로 객체를 선언하면, 자주 사용될 수록 힙 메모리 작성, 사용이 잦아지기 때문에 정적 지역변수로 선언
	//고정된 메모리 주소에, 계속 사용할 수 있는 공간을 마련해둔다.

	//정적 지역변수이기 때문에 데이터가 남아있을 수 있음 -> 함수 시작 시 객체에 담긴 데이터들을 모두 지워준다.
	queue.clear();
	vecNoneTarget.clear();

	CUI* pTargetUI = nullptr;

	queue.push_back(_pParentUI);

	while (queue.empty() != true)
	{
		//큐에 담긴 원소를 빼내고,
		CUI* pUI = queue.front();
		queue.pop_front();

		//마우스가 올려져 있는 자식UI라면, 타겟 UI가 될 수 있기에 리턴값으로 설정
		//이를 계속 반복하면, 최하단 UI이면서, 마우스가 올라가 있는 UI가 반환된다.
		if (pUI->isMouseOn())
		{
			//타겟 ui가 바뀔 때 기존 타겟은 타겟이 아니기에 논타겟 벡터로 삽입
			if (pTargetUI != nullptr)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			//마우스가 애초에 올라가지 않은 ui들은 당연히 논타겟으로 이동
			vecNoneTarget.push_back(pUI);
		}

		//그 원소가 자식을 가지고 있는지 체크
		const vector<CUI*>& vecChild = pUI->GetChildUI();

		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
		
	}

	//탐색 중 마우스 버튼이 떼졌다면, 타겟이 아닌 ui들에 대해서 마우스 눌림을 false로 변경
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}

CUI* CUIMgr::GetFocusedUI()
{
	//씬에서 UI 오브젝트 모음을 받아온다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	//기존 포커스 된 ui를 받아두고, 포커스된 ui가 바뀌었는지 확인
	CUI* pFocusedUI = m_pFocusedUI;

	return pFocusedUI;
}
