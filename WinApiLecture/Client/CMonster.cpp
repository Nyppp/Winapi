#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CCollider.h"
#include "AI.h"

#include <random>

CMonster::CMonster() : m_fSpeed(100.f), m_iHP(5), m_pAI(nullptr)
{
	//// �õ尪�� ��� ���� random_device ����.
	//std::random_device rd;

	//std::default_random_engine gen(rd());

	//// 0.5�� ~1�� ������ ���� �� �ο�
	//std::uniform_real_distribution<> dis(0.5f, 1.0f);

	//m_fRandomTime = dis(gen);

	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (m_pAI != nullptr)
		delete m_pAI;
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::update()
{
	m_pAI->update();
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	//���� ������Ʈ�� �÷��̾ �� �̻��Ͽ� ������ ������Ʈ ����
	//�׷��� �������̳�, ���� Ÿ�� ���� ������ �ٷ� ����� ���� �߻�
	//�ű��, �� �������� ������Ʈ���� �ٲ�� ������Ʈ�� ���� �� �����ε�, �������� �ٲ� ������ �ϰ� ��
	//������Ʈ ������ ���� �ϰ��� ���� �ʿ� -> �̺�Ʈ�� �̿�

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		--m_iHP;

		if(m_iHP <= 0)
			DeleteObject(this);
	}
}
