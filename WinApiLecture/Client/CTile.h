#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture* m_pTileTex;

    // -1�̸�, �ƹ��͵� �������� �ʰ� �ϱ����� int�� ����
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

