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

	//��Ŀ�� �� UI�� ���ٸ�, ��� ��Ȱ��ȭ �� UI �����̱⿡, �̺�Ʈ ó���� ����� �Ѵ�.
	if (m_pFocusedUI == nullptr)
	{
		return;
	}

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

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	//�̹� ��Ŀ�� �Ǿ��ִٸ� ��������
	//pUI�� �������� -> ��� ui�� ��Ŀ���� �����Ѵٴ� ������ ����
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
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	//���� ��Ŀ�� �� ui�� �޾Ƶΰ�, ��Ŀ���� ui�� �ٲ������ Ȯ��
	CUI* pFocusedUI = m_pFocusedUI;

	//���� Ŭ���� �ƿ� �Ͼ�� ���� -> UI ��Ŀ�� ���� X -> �����ȯ
	if (bLbtnTap == false)
	{
		return pFocusedUI;
	}

	vector<CObject*>::iterator iter = vecUI.begin();

	//��ȯ������ ������ Ÿ�� ���ͷ����� -> end�� �������� ������,
	//Ŭ���� �Ͼ���� UI�� �ƴ� ����� Ŭ������ ���� �����ϱ� ���ؼ�.
	vector<CObject*>::iterator targetiter = vecUI.end();

	//��Ŀ���� �Ƿ���, ���� Ŭ���� �߻��ؾ� �� -> �ش籸���� ����Ŭ���� �Ͼ ��쿡�� ����
	for (; iter != vecUI.end(); ++iter)
	{
		//UI�׷� ���ʹ� 0�� �ε����� ���� ��, �� �� �ε����� ���� �տ� �����ϴ� ������� �������� ��
		//���� ������� Ŭ�� ���θ� �˻��ϸ�, ������ UI�� ���� ��, �ڿ� �ִ°͵� �ڽ��� ��Ŀ�� �ƴٰ� �ν��� ������,
		//���ʹ� ������ ������ Ž���� �����ϱ� ������ Ŭ���� ���� �� UI�� �ᱹ ��Ŀ�� ��ȯ�� ��
		if (((CUI*)*iter)->isMouseOn())
		{
			targetiter = iter;
		}
	}
	
	//Ÿ�� ���ͷ����Ͱ� end�� ����Ų�ٴ� ����, Ŭ���� ������ ui�� ����� �ƴ϶�� �� -> �̺�Ʈ ó��X
	if (targetiter == vecUI.end())
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	//���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);

	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}
