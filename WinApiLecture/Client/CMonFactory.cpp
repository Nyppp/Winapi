#include "global.h"
#include "CMonFactory.h"
#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

//몬스터 생성을 팩토리 메서드화 시켜서, 반복적인 정보를 넣는 과정을 생략한다.
CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;
	switch (_eType)
	{
	//기본 타입 몬스터 생성
	case MON_TYPE::NORMAL:
	{
		//몬스터 객체
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		//몬스터 정보
		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fSpeed = 150.f;
		info.fHP = 100;

		pMon->SetMonInfo(info);

		//AI 생성
		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetAI(pAI);
	}
		break;

	//그 외에 특수 타입을 가진 몬스터의 생성도 구현 가능
	case MON_TYPE::RANGE:
	{

	}
		break;
	default:
		break;
	}

	//어떠한 케이스에도 걸리지 않고, 널포인터 반환을 방지하기 위해 assert
	assert(pMon);

	return pMon;
}
