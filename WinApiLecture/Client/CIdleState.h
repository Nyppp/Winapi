#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
private:

public:
    virtual void Enter();
    virtual void Exit();
    virtual void update();

public:
    //�θ� Ŭ���������� �⺻ �����ڸ� �����߱⿡, �ڽ� Ŭ���� ���� �⺻�����ڸ� ����� �� ����
    CIdleState();
    ~CIdleState();
};

