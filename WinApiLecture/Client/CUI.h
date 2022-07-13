#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    //Ui는 UI를 멤버 변수로 포함할 수 있음
    //자신의 자식 UI를 담은 벡터
    vector<CUI*> m_vecChildUI;

    //자신의 부모 ui -> nullptr이라면, 자신이 최상위 ui
    CUI* m_pParentUI;

    Vec2 m_vFinalPos;

public:
    CUI* GetParent() { return m_pParentUI; }
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

    Vec2 GetFinalPos() { return m_vFinalPos; }

private:
    void update_child();
    void render_child(HDC _dc);
    void finalupdate_child();
    

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void finalupdate();
    CLONE(CUI);

public:
    CUI();
    ~CUI();
};

