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
		//�ʱⰪ : idle �����̸� ������ ������ ����
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}

	//Ư�� Ű�� ���� ������ �̿� ���� ����ȭ �Ǿ�����
	//m_vecKey[(int)KEY::LEFT].eState;
	//m_vecKey[(int)KEY::LEFT].bPrev;
}

void CKeyMgr::update()
{
	//���� ���� �����찡 ��Ŀ�� �Ǿ��ִ��� üũ
	//���� Ȧ�� ���� ���� ���� �� �ڵ尡 ������, Ȧ�� ���� ������ â�� �������� ��쿡 ������ �߻��ϱ� ����
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

	//���� ��Ŀ�� �Ǿ��ִ� ������ �ڵ鰪�� ��ȯ�ϴ� ���α׷�
	HWND hWnd = GetFocus();

	//�����찡 ��Ŀ�� �� ����
	//�̷��� üũ���� ������, â�� ������ ���·� Ű�� ������ �����ϰ� ��
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//Ű�� ����
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrev == true)
				{
					//�������� �����־���
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					//������ �������� �ʾ���
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrev = true;
			}

			//Ű�� �ȴ�������
			else
			{
				if (m_vecKey[i].bPrev == true)
				{
					//������ �����־��� -> Ű�� �� ����
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//������ �������� �ʾҰ�, ���ݵ� �ȴ�������
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrev = false;
			}
		}
	}
	//������ ��Ŀ�� ��������
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//�ʱⰪ : idle �����̸� ������ ������ ����
			m_vecKey[i].bPrev = false;

			//Ű�� ���� ���¿��ٸ�, �� ���·� �ٲ���
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}

			//��� �� ���¿��ٸ� NONE���� �ٲ���
			//Ȥ��, ������ ���ȴٰ� ���� ���·� �ٲ� Ű���� ���¸� NONE���α��� �ǵ����� -> ��� AWAY�� �ӹ����� AWAY ���� �ڵ尡 ����Ǿ� �����߻�
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}
