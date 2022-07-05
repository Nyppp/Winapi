#pragma once

//시간, 프레임을 담당하는 CTimeMgr
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//FPS -> 1프레임당 시간 DeltaTime

	//Large integer -> 유니온(구조체 형태와 유사)
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double		m_dDT; // 프레임 사이의 시간값
	double		m_dACC; //1초를 재기 위한 누적 시간
	UINT		m_iCallCount; //초당 함수 호출횟수
	UINT		m_iFPS; //FPS
	

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

