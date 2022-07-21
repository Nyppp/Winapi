#pragma once
#include "CUI.h"

//다른 클래스의 함수를 호출해야 하기에 헤더간 참조를 사용
#include "CScene.h"
#include "CObject.h"


//void타입 포인터 이며, 2개의 매개변수까지 받을 수 있는 함수 포인터 타입 정의
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

//함수포인터를 선언할 때, 만약 가리키는 함수가 특정 클래스의 멤버 함수라면, 함수의 소속을 명시해야 함
//그러나, 원하는 함수가 다른 클래스의 함수 호출도 내포하고 있다면, 계속적으로 특정 클래스의 함수를 선언해야 함
//최상위 부모 클래스를 선언함으로서 자식관계에 있는 모든 클래스의 멤버로 접근이 가능함
//하지만 다른 상속관계의 클래스는 접근이 어려움 -> 애초부터 모든 최상위 상속 클래스를 하나로 묶는 더 최상위의 클래스가 필요함 -> 현재는 구조상 생략

//*** 다른 클래스의 멤버함수의 접근은, 헤더에서 직접 다른 헤더를 참조해야 함 -> 전방선언 사용 시, 함수를 정확히 인지하지 못해 함수를 불러오지 못한다.
typedef void(CScene ::*SCENE_MEMFUNC) (void);
typedef void(CObject::*OBJECT_MEMFUNC) (void);

class CBtnUI :
    public CUI
{
private:
    //멤버변수로 함수 포인터를 가진다. -> 버튼 클릭 시 해당 함수 호출
    BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

    SCENE_MEMFUNC m_pSceneFunc;
    //씬에 존재하는 함수를 호출할 객체
    CScene* m_pSceneInst;

    OBJECT_MEMFUNC m_pObjectFunc;
    //오브젝트에 존재하는 함수를 호출할 객체
    CObject* m_ObjectInst;

public:
    virtual void MouseOn(); //UI위에 마우스가 올라감
    virtual void MouseLbtnDown(); //UI위에서 마우스 왼쪽버튼이 눌려있음
    virtual void MouseLbtnUp(); //왼클릭 끝날 때
    virtual void MouseLbtnCliked();

    //버튼 클릭 시, 함수 콜백 - 전역함수 호출 시 동작
    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1 , DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    //씬 클래스 함수 호출시 동작(오버로딩)
    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);
    

    //오브젝트 클래스 함수 호출시 동작
    void SetClickedCallBack(CObject* _pObject, OBJECT_MEMFUNC _pObjectFunc);
    
    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

