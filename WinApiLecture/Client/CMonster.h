#pragma once
#include "CObject.h"

class AI;

class CMonster :
    public CObject
{
private:
    float   m_fSpeed; //�̵��ӵ�
    int m_iHP; //���� HP

    AI* m_pAI; //���Ͱ� ������ AI

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetAI(AI* _AI);

public:
    virtual void update();

    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CMonster);

public:
    CMonster();
    ~CMonster();
};

