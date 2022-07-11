#pragma once

class CObject;

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

public:
	void update();

private:
	void CalDiff();

};

