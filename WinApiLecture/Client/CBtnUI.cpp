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
	//함수포인터가 아무것도 가리키지 않으면, 기능이 없음 -> 조기종료
	if (m_pFunc == nullptr)
	{
		return;
	}
	else
	{
		m_pFunc(m_param1, m_param2);
	}
}
