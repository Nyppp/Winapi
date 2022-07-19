#pragma once
#include "CUI.h"

//voidŸ�� ������ �̸�, 2���� �Ű��������� ���� �� �ִ� �Լ� ������ Ÿ�� ����
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CBtnUI :
    public CUI
{
private:
    //��������� �Լ� �����͸� ������. -> ��ư Ŭ�� �� �ش� �Լ� ȣ��
    BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

public:
    virtual void MouseOn(); //UI���� ���콺�� �ö�
    virtual void MouseLbtnDown(); //UI������ ���콺 ���ʹ�ư�� ��������
    virtual void MouseLbtnUp(); //��Ŭ�� ���� ��
    virtual void MouseLbtnCliked();

    //��ư Ŭ�� ��, �Լ� �ݹ�
    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1 , DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

