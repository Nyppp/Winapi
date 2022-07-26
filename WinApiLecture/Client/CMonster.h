#pragma once
#include "CObject.h"

class AI;

class CMonster :
    public CObject
{
private:
    float   m_fSpeed; //이동속도
    int m_iHP; //몬스터 HP

    AI* m_pAI; //몬스터가 가지는 AI

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

