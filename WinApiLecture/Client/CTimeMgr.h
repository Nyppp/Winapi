#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//FPS -> 1�����Ӵ� �ð� DeltaTime

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

public:
	void init();
	
};

