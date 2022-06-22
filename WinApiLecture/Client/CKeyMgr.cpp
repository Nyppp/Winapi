#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'Z', 'X', 'C', 'V', 'B',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE
	//ALT, LSHIFT, SPACE, CTRL, ENTER, ESC,
	//LAST
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		//초기값 : idle 상태이며 이전에 눌리지 않음
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}

	//특정 키에 대한 접근은 이와 같이 색인화 되어있음
	//m_vecKey[(int)KEY::LEFT].eState;
	//m_vecKey[(int)KEY::LEFT].bPrev;
}

void CKeyMgr::update()
{
	//현재 메인 윈도우가 포커싱 되어있는지 체크
	//만약 홀드 동작 이후 뗐을 때 코드가 많은데, 홀드 도중 윈도우 창이 내려가는 경우에 문제가 발생하기 때문
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

	//현재 포커싱 되어있는 윈도우 핸들값을 반환하는 프로그램
	HWND hWnd = GetFocus();

	//윈도우가 포커싱 된 상태
	//이렇게 체크하지 않으면, 창이 내려간 상태로 키를 눌러도 동작하게 됨
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//키가 눌림
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrev == true)
				{
					//이전에도 눌려있었음
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					//이전에 눌려있지 않았음
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrev = true;
			}

			//키가 안눌려있음
			else
			{
				if (m_vecKey[i].bPrev == true)
				{
					//이전에 눌려있었음 -> 키를 막 뗐음
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//이전에 눌려있지 않았고, 지금도 안눌려있음
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrev = false;
			}
		}
	}
	//윈도우 포커싱 해제상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//초기값 : idle 상태이며 이전에 눌리지 않음
			m_vecKey[i].bPrev = false;

			//키가 눌린 상태였다면, 뗀 상태로 바꿔줌
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}

			//방금 뗀 상태였다면 NONE으로 바꿔줌
			//혹은, 위에서 눌렸다가 떼진 상태로 바뀐 키들의 상태를 NONE으로까지 되돌려줌 -> 계속 AWAY에 머무르면 AWAY 동작 코드가 실행되어 문제발생
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}
