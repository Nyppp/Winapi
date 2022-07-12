#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CEventMgr.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{} , m_pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] != nullptr)
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	//씬 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Start;

	//현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TOOL];
	//Enter는 가상함수기에 포인터가 가리키는 클래스의 Enter함수로 동작
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	//씬을 옮기기 이전, 현재 씬에서의 마무리처리
	m_pCurScene->Exit();

	//바로 씬을 바꾸면 이전 프레임에서 호출한 업데이트가 다음 프레임에서는 문제 발생 -> 이벤트로 처리
	m_pCurScene = m_arrScene[(UINT)_eNext];
	
	//씬을 옮기고 난 뒤 입장 처리
	m_pCurScene->Enter();
}
