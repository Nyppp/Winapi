#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//FPS -> 1프레임당 시간 DeltaTime

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

public:
	void init();
	
};

