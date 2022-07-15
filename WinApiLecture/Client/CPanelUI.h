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

    virtual void MouseOn(); //UI위에 마우스가 올라감
    virtual void MouseLbtnDown(); //UI위에서 마우스 왼쪽버튼이 눌려있음
    virtual void MouseLbtnUp(); //왼클릭 끝날 때

    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};

