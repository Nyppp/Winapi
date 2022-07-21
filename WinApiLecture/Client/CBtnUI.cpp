#include "CBtnUI.h"

CBtnUI::CBtnUI()
	: CUI(false), m_pFunc(nullptr), m_param1(0), m_param2(0),
	m_pObjectFunc(nullptr), m_pSceneFunc(nullptr),
	m_pSceneInst(nullptr), m_ObjectInst(nullptr)

{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnCliked()
{
	//�Լ������Ͱ� �ƹ��͵� ����Ű�� ������, ����� ���� -> ��������
	if (m_pFunc != nullptr)
	{
		m_pFunc(m_param1, m_param2);
	}
	
	if (m_pSceneInst && m_pSceneFunc)
	{
		//��ư�� ������ ��, scene ��ü�� �Լ��� null���� �ƴϸ�, �� ����� ȣ��
		(m_pSceneInst->*m_pSceneFunc)();
	}
}


void CBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneFunc = _pSceneFunc;
	m_pSceneInst = _pScene;
}

void CBtnUI::SetClickedCallBack(CObject* _pObject, OBJECT_MEMFUNC _pObjectFunc)
{
	m_pObjectFunc = _pObjectFunc;
	m_ObjectInst = _pObject;
}
