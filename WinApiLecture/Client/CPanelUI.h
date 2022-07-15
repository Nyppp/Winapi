#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2 m_vDragStart;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void MouseOn(); //UI���� ���콺�� �ö�
    virtual void MouseLbtnDown(); //UI������ ���콺 ���ʹ�ư�� ��������
    virtual void MouseLbtnUp(); //��Ŭ�� ���� ��

    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};

