#pragma once

#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_fTheta; //위 아래 방향

    Vec2 m_vDir; //이동방향벡터

public:
    CMissile();
    ~CMissile();

public:
    virtual void update();

    //미사일만은 동그라미로 그려내기 위해 오브젝트의 render함수를 오버라이딩 -> 클래스 다형성(polymorphism)
    virtual void render(HDC _dc);


    //각도를 전달받는 경우와, 벡터를 전달받는 경우 2가지로 방향 결정함수를 오버로딩
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir; 
        m_vDir.normalize();
    }
};

