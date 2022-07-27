#pragma once
#include "CObject.h"

class AI;

//��� ���Ͱ� ���������� ���� ���� ����ü
struct tMonInfo
{
    float   fSpeed; //�̵��ӵ�
    float   fHP; //���� HP
    float   fRecogRange; //�÷��̾� �ν� ����
    float   fAttRange; //���� ��Ÿ�
    float   fAtt; //���ݷ�
};

class CMonster :
    public CObject
{
private:
    tMonInfo m_tInfo; //���� ����
    AI* m_pAI; //���Ͱ� ������ AI

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

