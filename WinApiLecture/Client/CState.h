#pragma once

class AI;

class CState
{
private:
	AI* m_pAI; //������Ʈ�� ������ AI
	MON_STATE m_eState;

public:
	AI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }

public:
	//�ش� ����� �� ������Ʈ�� ���� �����ϱ� ���ؼ� �������̽��� ����	
	virtual void Enter() = 0; //������Ʈ�� ���� ��
	virtual void Exit() = 0; //������Ʈ�� ���� ��
	virtual void update() = 0;

public:
	CState(MON_STATE _eState);
	virtual ~CState(); //����� ���� ���� Ŭ�����̱� ������ �Ҹ��� �����Լ�ȭ

	friend class AI;
};

