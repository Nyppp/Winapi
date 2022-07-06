#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    float   m_fSpeed; //�̵��ӵ�
    Vec2    m_vCenterPos; //�̵��ݰ� ��,  �߾���ġ
    float   m_fMaxDistance; //�̵� �ݰ�
    int     m_iDir; //1 or -1 -> �̵�����

    float   m_fCurTime;
    float   m_fRandomTime;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }

    Vec2 GetCenterPos() { return Vec2(m_vCenterPos.x/2.f , m_vCenterPos.y/2.f); }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }

public:
    virtual void update();
    void CreateMonsterMissile();

    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMonster();
    ~CMonster();
};

