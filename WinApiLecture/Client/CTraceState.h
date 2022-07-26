#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
private:

public:
    virtual void Enter();
    virtual void Exit();
    virtual void update();

public:
    //부모 클래스에서의 기본 생성자를 제거했기에, 자식 클래스 또한 기본생성자를 사용할 수 없음
    CTraceState();
    ~CTraceState();
};

