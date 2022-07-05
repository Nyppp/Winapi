#pragma once

//�ð�, �������� ����ϴ� CTimeMgr
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//FPS -> 1�����Ӵ� �ð� DeltaTime

	//Large integer -> ���Ͽ�(����ü ���¿� ����)
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double		m_dDT; // ������ ������ �ð���
	double		m_dACC; //1�ʸ� ��� ���� ���� �ð�
	UINT		m_iCallCount; //�ʴ� �Լ� ȣ��Ƚ��
	UINT		m_iFPS; //FPS
	

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

