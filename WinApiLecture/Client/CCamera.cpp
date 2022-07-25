#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr), m_fTime(1.f), m_fSpeed(0.f), m_fAccTime(1.f),
	m_pVeilTex(nullptr), m_listCamEffect{}
{
	
}

CCamera::~CCamera()
{

}

void CCamera::init()
{
	//텍스쳐 생성에는 해상도가 필요하기에, 싱글톤 생성자에 해상도 값을 받아오는 게 아니라,
	//임의로 지정한 초기화 함수를 통해 명시적인 시점에서 코어 객체가 생성된 이후 가져온다
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"VeilTexture", (UINT)vResolution.x, (UINT)vResolution.y);

}

//오브젝트를 계속 따라다니게 함
void CCamera::update()
{
	if (m_pTargetObj != nullptr)
	{
		//dead처리된 오브젝트라면, 할당 해제
		if (m_pTargetObj->IsDead() == true)
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			SetLookAt(m_pTargetObj->GetPos());
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_vLookAt.y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_vLookAt.y += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_vLookAt.x -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_vLookAt.x += 500.f * fDT;
	}

	//화면 중앙좌표와 카메라 LookAt좌표의 차이 값 계산
	CalDiff();
}

void CCamera::render(HDC _dc)
{
	//아무런 카메라 효과가 없다면 검은 화면을 렌더링하지 않는다.
	if ( m_listCamEffect.empty() )
	{
		return;
	}
	
	float fRatio = 0.f;

	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDT;

	//전체 시간을 통해 0 ~ 255에 대한 비율을 계산하고 현재 시간에 대해 알파값 도출
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
	{
		fRatio = 0.f;
	}
	if (fRatio > 1.f)
	{
		fRatio = 1.f;
	}

	//페이드 효과에 적용할 알파값
	int iAlpha = 0;

	//페이드 아웃 -> 알파값 0에서 시간이 지날수록 255 -> 검은 텍스쳐가 서서히 나타나는 효과
	if (effect.eEffect == CAM_EFFECT::FADE_OUT)
	{
		//0부터 255로 알파값이 증가하는 페이드 아웃
		iAlpha = (int)(255.f * fRatio);
	}
	else if (effect.eEffect == CAM_EFFECT::FADE_IN)
	{
		//255부터 0으로 알파값이 감소하는 페이드 인
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	//해당 텍스쳐는 알파값이 없기에, 소스값이 없다고 설정하고 자체적으로 알파값을 준다.
	bf.SourceConstantAlpha = iAlpha;

	//32비트 비트맵 리소스에 대해서, 알파값을 참고하여 리소스를 그린다.
	AlphaBlend(_dc, 0, 0,
		(int)m_pVeilTex->Width(), (int)m_pVeilTex->Height(),
		m_pVeilTex->GetDC(), 0, 0,
		(int)m_pVeilTex->Width(), (int)m_pVeilTex->Height(),
		bf);

	if (effect.fCurTime >= effect.fDuration)
	{
		//현재 이펙트에 대해 시간처리가 완료되었다면, 리스트에서 꺼내고 다음 효과 연출
		m_listCamEffect.pop_front();
	}
}

//화면 중앙값과 카메라 좌표의 차를 계산하는 함수
void CCamera::CalDiff()
{
	//시간제한에 따른 등속 카메라 이동
	m_fAccTime += fDT;

	if (m_fAccTime > m_fTime)
	{
	m_vCurLookAt = m_vLookAt;
	}
	else
	{
	//카메라 위치가 바뀌었을 때, 이동해야 할 방향

		//m_vLookAt -> 목표 좌표 / m_vPrevLookAt 현재 좌표
		//하지만 씬 전환 시, 이전 카메라 좌표와 현재 카메라 좌표가 일치할 경우, 0 벡터에 대해 정규화를 하게 됨 -> 예외처리 필요
		Vec2 vLookDir = (m_vLookAt - m_vPrevLookAt);

		if (vLookDir.IsZero() != true)
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.normalize() * m_fSpeed * fDT;
		}

	}

	//부드러운 카메라 이동
	/*float fMoveDist = (m_vLookAt - m_vCurLookAt).Length();

	if (m_fSpeed < 10.f)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{

		Vec2 vLookDir = (m_vLookAt - m_vPrevLookAt);

		m_vCurLookAt = m_vPrevLookAt + vLookDir.normalize() * m_fSpeed * fDT * 2.f;

		m_fSpeed = (fMoveDist / (m_fTime));
		
	}*/

	//이전 LookAt과 현재 LookAt의 차이를 보정해서 현재 LookAt을 계산
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 Center = vResolution / 2.f;

	//카메라 위치 보정
	m_vDiff = m_vCurLookAt - Center;
	m_vPrevLookAt = m_vCurLookAt;
}
