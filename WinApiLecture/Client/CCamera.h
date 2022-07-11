#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	//카메라가 보고있는 위치(화면 중심)
	//카메라의 개념 -> 씬에 배치된 오브젝트들의 좌표는 모두 실제 좌표이지만,
	//카메라 상으로 나타난 좌표는 카메라 기준 좌표로, 게임 상 두개의 좌표 기준이 존재하게 됨
	Vec2 m_vLookAt;

	//이전에 본 카메라 위치
	Vec2 m_vPrevLookAt;

	//이전 위치와 현재위치 사이를 보간하는 위치(실제 사용 위치)
	Vec2 m_vCurLookAt;

	//카메라가 따라다닐 오브젝트
	CObject* m_pTargetObj;

	//화면 중앙좌표와 카메라 좌표의 차이값
	Vec2 m_vDiff;

	//카메라가 이동할 때 걸리는 시간
	float m_fTime;

	//카메라 이동 속도
	float m_fSpeed;

	//누적 시간
	float m_fAccTime;

public:
	void SetLookAt(Vec2 _vLook) 
	{ 
		m_vLookAt = _vLook;

		//현재좌표에서 목적지 사이의 거리
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		
		//두 지점 사이를 1초 안에 이동하는데 걸리는 속도
		m_fSpeed = fMoveDist / m_fTime;

		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

	Vec2 GetLookAt() { return m_vCurLookAt; }

	//렌더링 좌표 반환 = 실제 좌표에서 카메라 보간 값을 빼준다
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }

	//실제 좌표 반환 = 렌더링 좌표에서 카메라 보간 값을 더해준다
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

public:
	void update();

private:
	void CalDiff();

};

