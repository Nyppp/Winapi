#include "CBtnUI.h"

CBtnUI::CBtnUI() : CUI(false), m_pFunc(nullptr), m_param1(0), m_param2(0)
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
	if (m_pFunc == nullptr)
	{
		return;
	}
	else
	{
		m_pFunc(m_param1, m_param2);
	}
}
