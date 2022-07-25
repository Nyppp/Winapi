#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT eEffect; //ī�޶� ȿ��
	float fDuration; //ȿ�� ��ü ���� �ð�
	float fCurTime; //���� �ð�
};


class CCamera
{
	SINGLE(CCamera);
private:
	//ī�޶� �����ִ� ��ġ(ȭ�� �߽�)
	//ī�޶��� ���� -> ���� ��ġ�� ������Ʈ���� ��ǥ�� ��� ���� ��ǥ������,
	//ī�޶� ������ ��Ÿ�� ��ǥ�� ī�޶� ���� ��ǥ��, ���� �� �ΰ��� ��ǥ ������ �����ϰ� ��
	Vec2 m_vLookAt;

	//������ �� ī�޶� ��ġ
	Vec2 m_vPrevLookAt;

	//���� ��ġ�� ������ġ ���̸� �����ϴ� ��ġ(���� ��� ��ġ)
	Vec2 m_vCurLookAt;

	//ī�޶� ����ٴ� ������Ʈ
	CObject* m_pTargetObj;

	//ȭ�� �߾���ǥ�� ī�޶� ��ǥ�� ���̰�
	Vec2 m_vDiff;

	//ī�޶� �̵��� �� �ɸ��� �ð�
	float m_fTime;

	//ī�޶� �̵� �ӵ�
	float m_fSpeed;

	//���� �ð�
	float m_fAccTime;

	list<tCamEffect> m_listCamEffect; //ī�޶� ȿ�� ������ ��Ƶδ� ����Ʈ
	CTexture* m_pVeilTex; //������ �ؽ��� -> ���̵���, ���̵�ƿ� ȿ���� ���� ����

public:
	void SetLookAt(Vec2 _vLook) 
	{ 
		m_vLookAt = _vLook;

		//������ǥ���� ������ ������ �Ÿ�
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		
		//�� ���� ���̸� 1�� �ȿ� �̵��ϴµ� �ɸ��� �ӵ�
		m_fSpeed = fMoveDist / m_fTime;

		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

	Vec2 GetLookAt() { return m_vCurLookAt; }

	//������ ��ǥ ��ȯ = ���� ��ǥ���� ī�޶� ���� ���� ���ش�
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }

	//���� ��ǥ ��ȯ = ������ ��ǥ���� ī�޶� ���� ���� �����ش�
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	//���̵���, ���̵�ƿ� ���� �Լ�
	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		if (_fDuration == 0.f)
		{
			assert(nullptr);
		}

		m_listCamEffect.push_back(ef);
	}

	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		if (_fDuration == 0.f)
		{
			assert(nullptr);
		}
		m_listCamEffect.push_back(ef);
	}

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff();

};

