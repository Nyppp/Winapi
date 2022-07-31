#pragma once
#include "CScene.h"
class CScene_Start : public CScene
{
private:
    Vec2 m_vForcePos;
    float m_fForceRadius;
    float m_fCurRadius;
    float m_fForce;
    bool m_bUseForce;

public:
    //��ӹ��� �����Լ��� virtual�� ������ �ʾƵ� �����Ϸ��� �ν�������, ��������� ���� ���� -> �����ϱ� ���Ϸ���
    virtual void Enter();
    virtual void Exit();
    virtual void update();
    virtual void render(HDC _dc);

public:
    void CreateForce();

public:
    CScene_Start();
    ~CScene_Start();
};
