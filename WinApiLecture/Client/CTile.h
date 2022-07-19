#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture* m_pTileTex;

    // -1이면, 아무것도 참조하지 않게 하기위해 int로 지정
    int m_iImgIdx;

    int m_iMaximgIdx;


public:
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx()
    {
        ++m_iImgIdx;

        //텍스쳐 갯수를 넘어선 클릭이 들어오면 다시 0으로 만든다.
        if (m_iImgIdx == m_iMaximgIdx)
        {
            m_iImgIdx = 0;
        }
    }

private:
    virtual void render(HDC _dc);
    virtual void update();

    

public:
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    CLONE(CTile);

public:
    CTile();
    ~CTile();
};

