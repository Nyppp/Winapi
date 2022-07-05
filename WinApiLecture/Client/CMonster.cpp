#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CCollider.h"

#include <random>

CMonster::CMonster() : m_fSpeed(100.f), m_vCenterPos(Vec2(0.f, 0.f)), m_fMaxDistance(50.f), m_iDir(1), m_fCurTime(0.f), m_fRandomTime(0.f)
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
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	//�̵� ��������, �̵��ӵ���ŭ �ð��� ����Ͽ� �̵�
	vCurPos.x += fDT * m_fSpeed * m_iDir;
	
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	//�̵��ݰ��� �����, ���� ��ȯ
	if (0.f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	/* ���� : ���� �̻��� �߻� �ڵ� �ۼ� -> <random>��� ����Ͽ� ������ �ð����� �̻����� �߻��ϰ� �ڵ� �ۼ� */
	//�ð����� ��� ������Ų��.
	//m_fCurTime += fDT;

	////�������� �ο��� �̻��� �߻� �ð����� �����ϸ�, �̻��� �߻�
	//if (m_fCurTime >= m_fRandomTime)
	//{
	//	m_fCurTime = 0;
	//	//CreateMonsterMissile();
	//	
	//	//�� �� �̻��� �߻� �ð��� �ٽ� �����ϰ� ����(0.5�� ~ 1�� ������ ���� ��)
	//	std::random_device rd;
	//	std::default_random_engine gen(rd());
	//	std::uniform_real_distribution<> dis(0.5f, 1.0f);

	//	m_fRandomTime = dis(gen);
	//}
	
	SetPos(vCurPos);
}

//�̻��� �߻縦 ������ �������� �߻�
void CMonster::CreateMonsterMissile()
{
	//�̻��� ������Ʈ ��ü�� ����
	CMissile* pMissile = new CMissile;

	//�̻����� �߻��ϴ� ������Ʈ�� ��ġ(�÷��̾�) - �÷��̾� y�� ���� ���� = �̻����� �����Ǵ� ��ġ
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	//�̻��Ͽ� ���� �ʱ� ���� ����
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f,-1.f));

	//�� ��ü�� �����Ͽ�, ���Ŵ����� ���� ���� ���� �������� �� ���� �̻����� �߰��Ѵ�(�׸���)
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
