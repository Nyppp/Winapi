#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CCamera.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr),
	m_iCurFrm(0),
	m_pTex(nullptr),
	m_fAccTime(0.f),
	m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	//애니메이션 재생이 끝나면 return
	if (m_bFinish == true)
	{
		return;
	}

	//애니메이션이 재생 될 시간
	m_fAccTime += fDT;

	//재생 시간이 설정해둔 지속시간보다 커지면 다음 프레임으로 넘김
	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;

		//만약 프레임이 초과되면 return
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		//fDT를 불러오다가, 모종의 이유로 렉이 걸려서 처리가 늦어지면, 그 지연시간은 그대로 가져감
		//시간은 시간대로 보냈는데, 애니메이션 처리는 지연되면 문제 발생
		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish == true)
	{
		return;
	}

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset;

	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc,
		(int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f),
		(int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f),
		(int)(m_vecFrm[m_iCurFrm].vSlice.x),
		(int)(m_vecFrm[m_iCurFrm].vSlice.y),
		m_pTex->GetDC(),
		(int)(m_vecFrm[m_iCurFrm].vLT.x),
		(int)(m_vecFrm[m_iCurFrm].vLT.y),
		(int)(m_vecFrm[m_iCurFrm].vSlice.x),
		(int)(m_vecFrm[m_iCurFrm].vSlice.y),
		RGB(255, 0, 255));
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		//i가 0부터 시작하기 때문에 첫번째는 좌상단 그대로 이어감.
		frm.vLT = _vLT + _vStep * (int)i;

		m_vecFrm.push_back(frm);
	}
}
