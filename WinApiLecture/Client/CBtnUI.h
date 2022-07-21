#pragma once
#include "CUI.h"

//�ٸ� Ŭ������ �Լ��� ȣ���ؾ� �ϱ⿡ ����� ������ ���
#include "CScene.h"
#include "CObject.h"


//voidŸ�� ������ �̸�, 2���� �Ű��������� ���� �� �ִ� �Լ� ������ Ÿ�� ����
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

//�Լ������͸� ������ ��, ���� ����Ű�� �Լ��� Ư�� Ŭ������ ��� �Լ����, �Լ��� �Ҽ��� ����ؾ� ��
//�׷���, ���ϴ� �Լ��� �ٸ� Ŭ������ �Լ� ȣ�⵵ �����ϰ� �ִٸ�, ��������� Ư�� Ŭ������ �Լ��� �����ؾ� ��
//�ֻ��� �θ� Ŭ������ ���������μ� �ڽİ��迡 �ִ� ��� Ŭ������ ����� ������ ������
//������ �ٸ� ��Ӱ����� Ŭ������ ������ ����� -> ���ʺ��� ��� �ֻ��� ��� Ŭ������ �ϳ��� ���� �� �ֻ����� Ŭ������ �ʿ��� -> ����� ������ ����

//*** �ٸ� Ŭ������ ����Լ��� ������, ������� ���� �ٸ� ����� �����ؾ� �� -> ���漱�� ��� ��, �Լ��� ��Ȯ�� �������� ���� �Լ��� �ҷ����� ���Ѵ�.
typedef void(CScene ::*SCENE_MEMFUNC) (void);
typedef void(CObject::*OBJECT_MEMFUNC) (void);

class CBtnUI :
    public CUI
{
private:
    //��������� �Լ� �����͸� ������. -> ��ư Ŭ�� �� �ش� �Լ� ȣ��
    BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

    SCENE_MEMFUNC m_pSceneFunc;
    //���� �����ϴ� �Լ��� ȣ���� ��ü
    CScene* m_pSceneInst;

    OBJECT_MEMFUNC m_pObjectFunc;
    //������Ʈ�� �����ϴ� �Լ��� ȣ���� ��ü
    CObject* m_ObjectInst;

public:
    virtual void MouseOn(); //UI���� ���콺�� �ö�
    virtual void MouseLbtnDown(); //UI������ ���콺 ���ʹ�ư�� ��������
    virtual void MouseLbtnUp(); //��Ŭ�� ���� ��
    virtual void MouseLbtnCliked();

    //��ư Ŭ�� ��, �Լ� �ݹ� - �����Լ� ȣ�� �� ����
    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1 , DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    //�� Ŭ���� �Լ� ȣ��� ����(�����ε�)
    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);
    

    //������Ʈ Ŭ���� �Լ� ȣ��� ����
    void SetClickedCallBack(CObject* _pObject, OBJECT_MEMFUNC _pObjectFunc);
    
    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

