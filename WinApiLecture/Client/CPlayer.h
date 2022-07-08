#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
private:
    CTexture* m_pTex;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();

    CLONE(CPlayer);

public:
    CPlayer();

    //텍스쳐의 경우, 리소스를 사용해 모든 포인터가 같은 값을 가리키도록 설계되었기에
    //포인터가 같은 것을 가리키는 것을 신경쓰지 않고 복사 생성자 사용 -> 텍스쳐만 복사해오면 됨
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin), m_pTex(_origin.m_pTex)
    //{
    //}
    ~CPlayer();
};

