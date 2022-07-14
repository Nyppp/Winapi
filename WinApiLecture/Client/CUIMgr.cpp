#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CUI.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	//���� �����ϴ� �θ� UI���� ����
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	//��� UI�� Ž���ϸ� ���콺�� ���� �ִ��� üũ
	//�׷��� Ư�� UI�� ī�޶� ������� UI�� �ְ�, ���� ��ǥ�� ������ ī�޶� ������ ��ǥ�� �޶����� ui�� ����
	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		//�θ� UI�� ���� ���ϴ� �ڽ�ui�� ����
		pUI = GetTargetedUI(pUI);

		if (pUI != nullptr)
		{
			pUI->MouseOn();

			//��Ŭ���� �ƴٸ� LbtnDown �̺�Ʈ ȣ��
			if (bLbtnTap == true)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}

			//�ش� UI ������ ��Ŭ�� ���� �� -> LbtnUp �̺�Ʈ ȣ��
			else if (bLbtnAway == true)
			{
				pUI->MouseLbtnUp();

				//UI�� �����ִ� ���¿��� ���� �̺�Ʈ �Ѵ� �߻� -> Ŭ�� �̺�Ʈ�� ȣ���Ѵ�.
				if (pUI->m_bLbtnDown == true)
				{
					pUI->MouseLbtnCliked();
				}

				pUI->m_bLbtnDown = false;
			}
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
