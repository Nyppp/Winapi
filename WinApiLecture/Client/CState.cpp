#include "global.h"
#include "CState.h"

CState::CState(MON_STATE _eState)
	: m_pAI(nullptr), m_eState(_eState)
{
}

CState::~CState()
{
}
