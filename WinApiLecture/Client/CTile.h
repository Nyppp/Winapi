#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture* m_pTileTex;

    // -1�̸�, �ƹ��͵� �������� �ʰ� �ϱ����� int�� ����
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

        //�ؽ��� ������ �Ѿ Ŭ���� ������ �ٽ� 0���� �����.
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

