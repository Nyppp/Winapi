#pragma once
#include "CScene.h"
class CScene_Start : public CScene
{
private:


public:
    //��ӹ��� �����Լ��� virtual�� ������ �ʾƵ� �����Ϸ��� �ν�������, ��������� ���� ���� -> �����ϱ� ���Ϸ���
    virtual void Enter();
    virtual void Exit();
    virtual void update();

public:
    CScene_Start();
    ~CScene_Start();
};
