#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{
private:

public:
    virtual void MouseOn(); //UI위에 마우스가 올라감
    virtual void MouseLbtnDown(); //UI위에서 마우스 왼쪽버튼이 눌려있음
    virtual void MouseLbtnUp(); //왼클릭 끝날 때

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

