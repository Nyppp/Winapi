#pragma once

class AI;

class CState
{
private:
	AI* m_pAI; //스테이트를 보유한 AI
	MON_STATE m_eState;

public:
	AI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }

public:
	//해당 기능은 각 스테이트가 직접 구현하기 위해서 인터페이스로 만듦	
	virtual void Enter() = 0; //스테이트에 들어올 때
	virtual void Exit() = 0; //스테이트를 나갈 때
	virtual void update() = 0;

public:
	CState(MON_STATE _eState);
	virtual ~CState(); //상속을 위한 상위 클래스이기 때문에 소멸자 가상함수화

	friend class AI;
};

