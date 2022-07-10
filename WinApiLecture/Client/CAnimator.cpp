#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CObject.h"

CAnimator::CAnimator()
	: m_pOwner(nullptr), 
	m_pCurAnim(nullptr),
	m_bRepeat(true)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}



//������Ʈ ������Ʈ -> �ִϸ����� ������Ʈ -> ���� �ִϸ����Ͱ� ������ �ִϸ��̼� ������Ʈ
void CAnimator::update()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->update();
		
		//C++�ڵ� ����ȭ -> AND �����ڿ��� ���ǰ��� FALSE�� ���ǰ��� �˻� X
		//�׷��� AND�������� �պκп�, �˻� ������ ���� ���� ���� ���´�.
		if (m_bRepeat == true && m_pCurAnim->IsFinish() == true)
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->render(_dc);
	}
}

//�ؽ��� �̸�, �ؽ���, �»�� ��ġ, �ִϸ��̼� �ؽ��� ũ��, ���� ���������� �Ѿ�� ���� �»�� �̵��Ÿ�, ������ ����
void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	//�ִϸ��̼� �̸��� �̹� �����Ѵٸ�, assert �߻� -> ����ó��
	CAnimation* pAnim  = FindAnimation(_strName);
	assert(pAnim == nullptr);

	pAnim = new CAnimation;

	//�ִϸ��̼��� �̸� ����
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	//�޾ƿ� �ؽ��Ŀ� ��ǥ ������ ����� �ִϸ��̼� Ŭ������ �Ѿ�� �ִϸ��̼� ����
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	//�ִϸ��̼��� ������ ����, �ִϸ��̼� map�� ���� ����
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}


void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}