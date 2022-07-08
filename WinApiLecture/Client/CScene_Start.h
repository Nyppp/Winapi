#pragma once
#include "CScene.h"
class CScene_Start : public CScene
{
private:


public:
    //상속받은 가상함수는 virtual을 붙이지 않아도 컴파일러가 인식하지만, 명시적으로 선언도 가능 -> 구분하기 편하려고
    virtual void Enter();
    virtual void Exit();
    virtual void update();

public:
    CScene_Start();
    ~CScene_Start();
};
