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
	//�ؽ��� �������� �ػ󵵰� �ʿ��ϱ⿡, �̱��� �����ڿ� �ػ� ���� �޾ƿ��� �� �ƴ϶�,
	//���Ƿ� ������ �ʱ�ȭ �Լ��� ���� ������� �������� �ھ� ��ü�� ������ ���� �����´�
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"VeilTexture", (UINT)vResolution.x, (UINT)vResolution.y);

}

//������Ʈ�� ��� ����ٴϰ� ��
void CCamera::update()
{
	if (m_pTargetObj != nullptr)
	{
		//deadó���� ������Ʈ���, �Ҵ� ����
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

	//ȭ�� �߾���ǥ�� ī�޶� LookAt��ǥ�� ���� �� ���
	CalDiff();
}

void CCamera::render(HDC _dc)
{
	//�ƹ��� ī�޶� ȿ���� ���ٸ� ���� ȭ���� ���������� �ʴ´�.
	if ( m_listCamEffect.empty() )
	{
		return;
	}
	
	float fRatio = 0.f;

	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDT;

	//��ü �ð��� ���� 0 ~ 255�� ���� ������ ����ϰ� ���� �ð��� ���� ���İ� ����
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
	{
		fRatio = 0.f;
	}
	if (fRatio > 1.f)
	{
		fRatio = 1.f;
	}

	//���̵� ȿ���� ������ ���İ�
	int iAlpha = 0;

	//���̵� �ƿ� -> ���İ� 0���� �ð��� �������� 255 -> ���� �ؽ��İ� ������ ��Ÿ���� ȿ��
	if (effect.eEffect == CAM_EFFECT::FADE_OUT)
	{
		//0���� 255�� ���İ��� �����ϴ� ���̵� �ƿ�
		iAlpha = (int)(255.f * fRatio);
	}
	else if (effect.eEffect == CAM_EFFECT::FADE_IN)
	{
		//255���� 0���� ���İ��� �����ϴ� ���̵� ��
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	//�ش� �ؽ��Ĵ� ���İ��� ���⿡, �ҽ����� ���ٰ� �����ϰ� ��ü������ ���İ��� �ش�.
	bf.SourceConstantAlpha = iAlpha;

	//32��Ʈ ��Ʈ�� ���ҽ��� ���ؼ�, ���İ��� �����Ͽ� ���ҽ��� �׸���.
	AlphaBlend(_dc, 0, 0,
		(int)m_pVeilTex->Width(), (int)m_pVeilTex->Height(),
		m_pVeilTex->GetDC(), 0, 0,
		(int)m_pVeilTex->Width(), (int)m_pVeilTex->Height(),
		bf);

	if (effect.fCurTime >= effect.fDuration)
	{
		//���� ����Ʈ�� ���� �ð�ó���� �Ϸ�Ǿ��ٸ�, ����Ʈ���� ������ ���� ȿ�� ����
		m_listCamEffect.pop_front();
	}
}

//ȭ�� �߾Ӱ��� ī�޶� ��ǥ�� ���� ����ϴ� �Լ�
void CCamera::CalDiff()
{
	//�ð����ѿ� ���� ��� ī�޶� �̵�
	m_fAccTime += fDT;

	if (m_fAccTime > m_fTime)
	{
	m_vCurLookAt = m_vLookAt;
	}
	else
	{
	//ī�޶� ��ġ�� �ٲ���� ��, �̵��ؾ� �� ����

		//m_vLookAt -> ��ǥ ��ǥ / m_vPrevLookAt ���� ��ǥ
		//������ �� ��ȯ ��, ���� ī�޶� ��ǥ�� ���� ī�޶� ��ǥ�� ��ġ�� ���, 0 ���Ϳ� ���� ����ȭ�� �ϰ� �� -> ����ó�� �ʿ�
		Vec2 vLookDir = (m_vLookAt - m_vPrevLookAt);

		if (vLookDir.IsZero() != true)
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.normalize() * m_fSpeed * fDT;
		}

	}

	//�ε巯�� ī�޶� �̵�
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

	//���� LookAt�� ���� LookAt�� ���̸� �����ؼ� ���� LookAt�� ���
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 Center = vResolution / 2.f;

	//ī�޶� ��ġ ����
	m_vDiff = m_vCurLookAt - Center;
	m_vPrevLookAt = m_vCurLookAt;
}
