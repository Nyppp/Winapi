#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{
private:

public:
    virtual void MouseOn(); //UI���� ���콺�� �ö�
    virtual void MouseLbtnDown(); //UI������ ���콺 ���ʹ�ư�� ��������
    virtual void MouseLbtnUp(); //��Ŭ�� ���� ��

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

