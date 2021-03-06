#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
private:
    HDC     m_dc;
    HBITMAP m_hBit;
    BITMAP m_bitInfo;

public:
    //텍스쳐에 비트맵을 불러오는 함수
    void Load(const wstring& _strFilePath);
    void Create(UINT _iWidth, UINT _iHeight);

    //텍스쳐의 가로, 세로 길이 반환 함수
    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }


//텍스쳐 객체를 아무나 생성할수 없고, 리소스 관리자만 실행할 수 있도록 friend 선언
private:
    CTexture();
    virtual  ~CTexture();

    friend class CResMgr;
};

