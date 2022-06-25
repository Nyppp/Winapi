#pragma once

#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_fDir; //�� �Ʒ� ����

public:
    CMissile();
    ~CMissile();

public:
    virtual void update();

    //�̻��ϸ��� ���׶�̷� �׷����� ���� ������Ʈ�� render�Լ��� �������̵� -> Ŭ���� ������(polymorphism)
    virtual void render(HDC _dc);

    void SetDir(bool _bUp)
    {
        if (_bUp == true)
        {
            m_fDir = -1.f;
        }
        else
        {
            m_fDir = 1.f;
        }
    }
};

