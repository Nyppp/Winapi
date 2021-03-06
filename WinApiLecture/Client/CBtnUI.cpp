#include "CBtnUI.h"

CBtnUI::CBtnUI()
	: CUI(false), m_pFunc(nullptr), m_param1(0), m_param2(0),
	m_pObjectFunc(nullptr), m_pSceneFunc(nullptr),
	m_pSceneInst(nullptr), m_ObjectInst(nullptr), m_strBtnText{}
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
	//함수포인터가 아무것도 가리키지 않으면, 기능이 없음 -> 조기종료
	if (m_pFunc != nullptr)
	{
		m_pFunc(m_param1, m_param2);
	}
	
	if (m_pSceneInst && m_pSceneFunc)
	{
		//버튼이 눌렸을 때, scene 객체와 함수가 null값이 아니면, 그 기능을 호출
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

void CBtnUI::render(HDC _dc)
{
	CUI::render(_dc);

	//UI버튼의 사각형 공간 정보 저장(finalpos로 저장된 좌표가 상대좌표이기에, 상속관계의 버튼의 정상적 위치 받아올 수 있음)
	RECT rt = { GetFinalPos().x, GetFinalPos().y, GetFinalPos().x + GetScale().x, GetFinalPos().y + GetScale().y };

	//한줄 출력 + 수직 가운데 위치 + 수평 가운데에서 버튼 UI의 텍스트 출력
	DrawText(_dc, m_strBtnText.c_str(), -1, &rt, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}
