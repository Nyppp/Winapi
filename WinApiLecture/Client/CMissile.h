#pragma once

#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_fDir; //위 아래 방향

public:
    CMissile();
    ~CMissile();

public:
    virtual void update();

    //미사일만은 동그라미로 그려내기 위해 오브젝트의 render함수를 오버라이딩 -> 클래스 다형성(polymorphism)
    virtual void render(HDC _dc);

    void SetDir(bool _bUp)
    {
        if (_bUp == true)
        {
            m_fDir = -1.f;
        }
        else
        {
            m_fDir = 1.f;
        }
    }
};

