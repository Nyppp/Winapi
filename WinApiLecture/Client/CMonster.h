#pragma once
#include "CObject.h"

class AI;

//모든 몬스터가 공통적으로 가질 정보 구조체
struct tMonInfo
{
    float   fSpeed; //이동속도
    float   fHP; //몬스터 HP
    float   fRecogRange; //플레이어 인식 범위
    float   fAttRange; //공격 사거리
    float   fAtt; //공격력
};

class CMonster :
    public CObject
{
private:
    tMonInfo m_tInfo; //몬스터 정보
    AI* m_pAI; //몬스터가 가지는 AI

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);
    const tMonInfo& GetMonInfo() { return m_tInfo; }

private:
    void SetMonInfo(const tMonInfo& _info)
    {
        m_tInfo = _info;
    }

public:
    virtual void update();

    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CMonster);

public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;
};

