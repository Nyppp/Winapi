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
	// 1. FocusedUI Ȯ��
	// ���� ��Ŀ���� �����ؾ� �ϴ���, ���ο� ��Ŀ�� �� ui�� �ִ��� �Ǵ�
	m_pFocusedUI = GetFocusedUI();

	// 2. ��Ŀ�� �� ui ������, �ڽ� ui�� �� Ÿ���� ui�� �����´�.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (pTargetUI != nullptr)
	{
		pTargetUI->MouseOn();

		//��Ŭ���� �ƴٸ� LbtnDown �̺�Ʈ ȣ��
		if (bLbtnTap == true)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}

		//�ش� UI ������ ��Ŭ�� ���� �� -> LbtnUp �̺�Ʈ ȣ��
		else if (bLbtnAway == true)
		{
			pTargetUI->MouseLbtnUp();

			//UI�� �����ִ� ���¿��� ���� �̺�Ʈ �Ѵ� �߻� -> Ŭ�� �̺�Ʈ�� ȣ���Ѵ�.
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
	//��ư�� �����ִ��� ����
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	//�θ�UI ����, ��� �ڽĵ��� �˻�(BFS�˰��� ���)
	static list<CUI*> queue;

	//Ÿ�� ui�� �ƴ� �͵��� ���� ����
	static vector<CUI*> vecNoneTarget;

	//�Լ��� ���������� ��ü�� �����ϸ�, ���� ���� ���� �� �޸� �ۼ�, ����� ������� ������ ���� ���������� ����
	//������ �޸� �ּҿ�, ��� ����� �� �ִ� ������ �����صд�.

	//���� ���������̱� ������ �����Ͱ� �������� �� ���� -> �Լ� ���� �� ��ü�� ��� �����͵��� ��� �����ش�.
	queue.clear();
	vecNoneTarget.clear();

	CUI* pTargetUI = nullptr;

	queue.push_back(_pParentUI);

	while (queue.empty() != true)
	{
		//ť�� ��� ���Ҹ� ������,
		CUI* pUI = queue.front();
		queue.pop_front();

		//���콺�� �÷��� �ִ� �ڽ�UI���, Ÿ�� UI�� �� �� �ֱ⿡ ���ϰ����� ����
		//�̸� ��� �ݺ��ϸ�, ���ϴ� UI�̸鼭, ���콺�� �ö� �ִ� UI�� ��ȯ�ȴ�.
		if (pUI->isMouseOn())
		{
			//Ÿ�� ui�� �ٲ� �� ���� Ÿ���� Ÿ���� �ƴϱ⿡ ��Ÿ�� ���ͷ� ����
			if (pTargetUI != nullptr)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			//���콺�� ���ʿ� �ö��� ���� ui���� �翬�� ��Ÿ������ �̵�
			vecNoneTarget.push_back(pUI);
		}

		//�� ���Ұ� �ڽ��� ������ �ִ��� üũ
		const vector<CUI*>& vecChild = pUI->GetChildUI();

		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
		
	}

	//Ž�� �� ���콺 ��ư�� �����ٸ�, Ÿ���� �ƴ� ui�鿡 ���ؼ� ���콺 ������ false�� ����
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
	//������ UI ������Ʈ ������ �޾ƿ´�.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	//���� ��Ŀ�� �� ui�� �޾Ƶΰ�, ��Ŀ���� ui�� �ٲ������ Ȯ��
	CUI* pFocusedUI = m_pFocusedUI;

	return pFocusedUI;
}
