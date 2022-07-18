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

	//포커스 된 UI가 없다면, 모두 비활성화 된 UI 상태이기에, 이벤트 처리가 없어야 한다.
	if (m_pFocusedUI == nullptr)
	{
		return;
	}

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

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	//이미 포커스 되어있다면 조기종료
	//pUI가 널포인터 -> 모든 ui의 포커스를 해제한다는 뜻으로 간주
	if (m_pFocusedUI == _pUI || _pUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	vecUI.erase(iter);

	vecUI.push_back(m_pFocusedUI);

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
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	//기존 포커스 된 ui를 받아두고, 포커스된 ui가 바뀌었는지 확인
	CUI* pFocusedUI = m_pFocusedUI;

	//왼쪽 클릭이 아예 일어나지 않음 -> UI 포커스 변경 X -> 조기반환
	if (bLbtnTap == false)
	{
		return pFocusedUI;
	}

	vector<CObject*>::iterator iter = vecUI.begin();

	//반환값으로 가져갈 타켓 이터레이터 -> end로 지정해준 이유는,
	//클릭은 일어났지만 UI가 아닌 허공을 클릭했을 때를 구분하기 위해서.
	vector<CObject*>::iterator targetiter = vecUI.end();

	//포커스가 되려면, 왼쪽 클릭이 발생해야 함 -> 해당구간은 왼쪽클릭이 일어난 경우에만 동작
	for (; iter != vecUI.end(); ++iter)
	{
		//UI그룹 벡터는 0번 인덱스가 가장 뒤, 맨 뒤 인덱스가 가장 앞에 존재하는 방법으로 렌더링이 됨
		//벡터 순서대로 클릭 여부를 검색하면, 겹쳐진 UI가 있을 때, 뒤에 있는것도 자신이 포커스 됐다고 인식을 하지만,
		//벡터는 어차피 끝까지 탐색을 진행하기 때문에 클릭된 가장 앞 UI가 결국 포커스 전환이 됨
		if (((CUI*)*iter)->isMouseOn())
		{
			targetiter = iter;
		}
	}
	
	//타겟 이터레이터가 end를 가리킨다는 뜻은, 클릭은 됐지만 ui가 대상이 아니라는 뜻 -> 이벤트 처리X
	if (targetiter == vecUI.end())
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	//벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);

	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}
