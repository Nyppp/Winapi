#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    //Ui�� UI�� ��� ������ ������ �� ����
    //�ڽ��� �ڽ� UI�� ���� ����
    //���� ���� ��, ���Ͱ� ���� �ڽ�UI�� ����Ű�⿡ ���� ������ ȣ�� �� ���� �߻� -> ���� ������ ���� �ؾ���
    vector<CUI*> m_vecChildUI;

    //�ڽ��� �θ� ui -> nullptr�̶��, �ڽ��� �ֻ��� ui
    CUI* m_pParentUI;

    Vec2 m_vFinalPos;

    //UI�� ī�޶� ���� �����̴��� ����
    bool m_bCameraAffected;
    //���콺�� ui���� �ִ��� ����
    bool m_bMouseOn;
    //UI�� Ŭ���� �� �ִ��� ����
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


    //UI �̺�Ʈ
public:
    virtual void MouseOn(); //UI���� ���콺�� �ö�
    virtual void MouseLbtnDown(); //UI������ ���콺 ���ʹ�ư�� ��������
    virtual void MouseLbtnUp(); //��Ŭ�� ���� ��
    virtual void MouseLbtnCliked(); //Ŭ�� -> �� ������ ������ ���� ���ۿ� ���� �̺�Ʈ


    void MouseOnCheck();

    //click �̺�Ʈ�� down �̺�Ʈ�� ����
    //down �̺�Ʈ -> ����������, �������� or ���� ä�� �ٸ������� ���콺 �巡�� �Ͽ� ui ��� ä�� ���콺��ư ��� btnup ȣ��x
    //clikc �̺�Ʈ -> �ش� UI�� ������, ���� ������ �Ѵ� ���Ե� �̺�Ʈ



public:
    //ī�޶� ���� ������ �ݵ�� �ʿ��ϱ⿡, �⺻ �����ڸ� ���ְ� ���ڸ� �޵��� ����
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;
};

