#pragma once
#include "CUI.h"

//void타입 포인터 이며, 2개의 매개변수까지 받을 수 있는 함수 포인터 타입 정의
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CBtnUI :
    public CUI
{
private:
    //멤버변수로 함수 포인터를 가진다. -> 버튼 클릭 시 해당 함수 호출
    BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

public:
    virtual void MouseOn(); //UI위에 마우스가 올라감
    virtual void MouseLbtnDown(); //UI위에서 마우스 왼쪽버튼이 눌려있음
    virtual void MouseLbtnUp(); //왼클릭 끝날 때
    virtual void MouseLbtnCliked();

    //버튼 클릭 시, 함수 콜백
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

