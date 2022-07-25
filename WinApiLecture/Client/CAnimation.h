#pragma once

#include "global.h"

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2 vLT;
	Vec2 vSlice;
	Vec2 vOffset;
	float fDuration;
};

class CAnimation
{
private:
	wstring m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex; //애니메이션이 사용하는 텍스쳐
	vector<tAnimFrm> m_vecFrm; //모든 프레임의 정보
	int m_iCurFrm; //현재 프레임
	float m_fAccTime; //시간 누적

	bool m_bFinish;

public:
	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, Vec2 _vOffset);

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	//특정 프레임 반환
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }

	int GetMaxFrame() { return m_vecFrm.size(); }


private:
	//중복된 이름이나, 다른 곳에서 막 접근할수 없게 이름 지정은 private
	void SetName(const wstring& _strName) { m_strName = _strName; }



public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

