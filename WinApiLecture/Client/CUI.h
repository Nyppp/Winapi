#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    //Ui�� UI�� ��� ������ ������ �� ����
    //�ڽ��� �ڽ� UI�� ���� ����
    vector<CUI*> m_vecChildUI;

    //�ڽ��� �θ� ui -> nullptr�̶��, �ڽ��� �ֻ��� ui
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

