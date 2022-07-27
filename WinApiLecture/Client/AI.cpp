#include "global.h"
#include "AI.h"
#include "CState.h"
#include "CMonster.h"

AI::AI()
	: m_pCurState(nullptr)
{
}

AI::~AI()
{
	Safe_Delete_Map(m_mapState);
}

void AI::update()
{
	m_pCurState->update();
}

void AI::AddState(CState* _pState)
{
	CState* pState = GetState(_pState->GetType());
	assert(!pState);
	_pState->m_pAI = this;

	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	
}

CState* AI::GetState(MON_STATE _eState)
{
	map<MON_STATE, CState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void AI::SetCurState(MON_STATE _eState)
{
	//AI의 현재 상태를 지정
	m_pCurState = GetState(_eState);
	
	//AI에 존재하지 않는 상태라면 예외처리
	assert(m_pCurState);
}

void AI::ChangeState(MON_STATE _eNextState)
{
	CState* pNextState = GetState(_eNextState);
	if (m_pCurState == pNextState || pNextState == nullptr)
	{
		assert(nullptr);
	}

	m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}
