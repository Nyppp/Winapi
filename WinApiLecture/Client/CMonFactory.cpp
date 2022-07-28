#include "global.h"
#include "CMonFactory.h"
#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

//���� ������ ���丮 �޼���ȭ ���Ѽ�, �ݺ����� ������ �ִ� ������ �����Ѵ�.
CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;
	switch (_eType)
	{
	//�⺻ Ÿ�� ���� ����
	case MON_TYPE::NORMAL:
	{
		//���� ��ü
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		//���� ����
		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fSpeed = 150.f;
		info.fHP = 100;

		pMon->SetMonInfo(info);

		//AI ����
		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetAI(pAI);
	}
		break;

	//�� �ܿ� Ư�� Ÿ���� ���� ������ ������ ���� ����
	case MON_TYPE::RANGE:
	{

	}
		break;
	default:
		break;
	}

	//��� ���̽����� �ɸ��� �ʰ�, �������� ��ȯ�� �����ϱ� ���� assert
	assert(pMon);

	return pMon;
}