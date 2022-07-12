#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture* m_pTileTex;

    // -1이면, 아무것도 참조하지 않게 하기위해 int로 지정
    int m_iIdx;


public:
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

private:
    virtual void render(HDC _dc);
    virtual void update();

    CLONE(CTile);

public:
    CTile();
    ~CTile();
};

