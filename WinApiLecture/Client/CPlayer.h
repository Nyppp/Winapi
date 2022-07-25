#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
private:
    Vec2 m_FireDir;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();

    CLONE(CPlayer);

public:
    CPlayer();

    //�ؽ����� ���, ���ҽ��� ����� ��� �����Ͱ� ���� ���� ����Ű���� ����Ǿ��⿡
    //�����Ͱ� ���� ���� ����Ű�� ���� �Ű澲�� �ʰ� ���� ������ ��� -> �ؽ��ĸ� �����ؿ��� ��
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin), m_pTex(_origin.m_pTex)
    //{
    //}
    ~CPlayer();
};

