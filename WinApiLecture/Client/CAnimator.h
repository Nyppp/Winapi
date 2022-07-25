#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	//������Ʈ
	CObject* m_pOwner;

	//��� �ִϸ��̼� ����
	map<wstring, CAnimation*> m_mapAnim;

	//���� ������� �ִϸ��̼�
	CAnimation* m_pCurAnim;

	//�ִϸ��̼� �ݺ���� ����
	bool m_bRepeat;

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, Vec2 _vOffset);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void render(HDC _dc);
	void finalupdate();

	CObject* GetObj() { return m_pOwner; }

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

