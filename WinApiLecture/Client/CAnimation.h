#pragma once

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
	CTexture* m_pTex; //�ִϸ��̼��� ����ϴ� �ؽ���
	vector<tAnimFrm> m_vecFrm; //��� �������� ����
	int m_iCurFrm; //���� ������
	float m_fAccTime; //�ð� ����

	bool m_bFinish;

public:
	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	//Ư�� ������ ��ȯ
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }

	int GetMaxFrame() { return m_vecFrm.size(); }


private:
	//�ߺ��� �̸��̳�, �ٸ� ������ �� �����Ҽ� ���� �̸� ������ private
	void SetName(const wstring& _strName) { m_strName = _strName; }



public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};
