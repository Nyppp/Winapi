#pragma once

#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_fTheta; //�� �Ʒ� ����

    Vec2 m_vDir; //�̵����⺤��

public:
    CMissile();
    ~CMissile();

public:
    virtual void update();

    //�̻��ϸ��� ���׶�̷� �׷����� ���� ������Ʈ�� render�Լ��� �������̵� -> Ŭ���� ������(polymorphism)
    virtual void render(HDC _dc);


    //������ ���޹޴� ����, ���͸� ���޹޴� ��� 2������ ���� �����Լ��� �����ε�
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir; 
        m_vDir.normalize();
    }
};

