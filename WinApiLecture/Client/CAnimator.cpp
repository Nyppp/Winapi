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



//오브젝트 업데이트 -> 애니메이터 업데이트 -> 현재 애니메이터가 지정한 애니메이션 업데이트
void CAnimator::update()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->update();
		
		//C++코드 최적화 -> AND 연산자에서 앞의것이 FALSE면 뒤의것은 검사 X
		//그래서 AND연산자의 앞부분에, 검사 수행이 적은 것을 먼저 적는다.
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

//텍스쳐 이름, 텍스쳐, 좌상단 위치, 애니메이션 텍스쳐 크기, 다음 프레임으로 넘어가기 위해 좌상단 이동거리, 프레임 갯수
void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	//애니메이션 이름이 이미 존재한다면, assert 발생 -> 예외처리
	CAnimation* pAnim  = FindAnimation(_strName);
	assert(pAnim == nullptr);

	pAnim = new CAnimation;

	//애니메이션의 이름 설정
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	//받아온 텍스쳐와 좌표 정보를 사용해 애니메이션 클래스로 넘어가서 애니메이션 생성
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	//애니메이션이 생성된 이후, 애니메이션 map에 정보 저장
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