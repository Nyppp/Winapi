#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    //Ui는 UI를 멤버 변수로 포함할 수 있음
    //자신의 자식 UI를 담은 벡터
    //얕은 복사 시, 벡터가 같은 자식UI를 가리키기에 복사 생성자 호출 시 문제 발생 -> 복사 생성자 설정 해야함
    vector<CUI*> m_vecChildUI;

    //자신의 부모 ui -> nullptr이라면, 자신이 최상위 ui
    CUI* m_pParentUI;

    Vec2 m_vFinalPos;

    //UI가 카메라를 따라 움직이는지 유무
    bool m_bCameraAffected;
    //마우스가 ui위에 있는지 유무
    bool m_bMouseOn;
    //UI가 클릭된 적 있는지 유무
    bool m_bLbtnDown;

public:
    CUI* GetParent() { return m_pParentUI; }
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    Vec2 GetFinalPos() { return m_vFinalPos; }

    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

    bool isMouseOn() { return m_bMouseOn; }
    bool isLbtnDown() { return m_bLbtnDown; }

private:
    void update_child();
    void render_child(HDC _dc);
    void finalupdate_child();
    

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void finalupdate();

    virtual CUI* Clone() = 0;


    //UI 이벤트
public:
    virtual void MouseOn(); //UI위에 마우스가 올라감
    virtual void MouseLbtnDown(); //UI위에서 마우스 왼쪽버튼이 눌려있음
    virtual void MouseLbtnUp(); //왼클릭 끝날 때
    virtual void MouseLbtnCliked(); //클릭 -> 한 순간에 눌리고 떼진 동작에 대한 이벤트


    void MouseOnCheck();

    //click 이벤트와 down 이벤트의 차이
    //down 이벤트 -> 눌려있지만, 떼지않음 or 눌린 채로 다른곳으로 마우스 드래그 하여 ui 벗어난 채로 마우스버튼 뗴면 btnup 호출x
    //clikc 이벤트 -> 해당 UI를 누르고, 떼는 과정이 둘다 포함된 이벤트



public:
    //카메라 영향 변수는 반드시 필요하기에, 기본 생성자를 없애고 인자를 받도록 설정
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;
};

