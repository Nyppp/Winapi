#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"




CCollisionMgr::CCollisionMgr() : m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
	
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		//���� �׷����� �Ѿ ����, �̹� üũ �� ���谡 �ֱ� ������ ���� iRow���� ����
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			//�浹 ���� ���̺��� �ѷ����鼭 �浹���谡 �����Ǵ� �� ������Ʈ�� �ִٸ�,
			//��¥�� �� ��ü�� �浹�ϴ��� üũ
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}

		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//���� ���ڸ� ���� �׷�Ÿ���� ������, ū���� ���� ����Ѵ�

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}


	//iRow��° �迭��, iCol��ŭ 1�� shift�� ���� ����ִ´�(��Ʈ�������� 2�����迭 ��ü)
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		//�̹� �����Ѵٸ�, 1�Ǻ������� and����(�ش� ��Ʈ �κи� ����)
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		//�� �ܿ��� ��Ʈ ����
		m_arrCheck[iRow] |= (1 << iCol);
	}

}

//�׷� �� �浹 ����
void CCollisionMgr::CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	
	//��ȯŸ������ ���� Ÿ���� ��ȯ�ϴ� �Լ��� ���������� �����ϸ�, �װ��� ������ �ƴ�.
	//������ �޴� ������ const ���� Ÿ������ �����ؾ� ���� ��ü�� ����Ű�� ��
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter;

	//�� �׷쿡 ���� ��� ������Ʈ�� Ž��
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		//�ش� ������Ʈ�� �浹ü�� ���ٸ� �ش� ������Ʈ ����
		if (vecLeft[i]->GetCollider() == nullptr)
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			//�ش� ������Ʈ�� �浹ü�� ���ٸ� �ش� ������Ʈ ����
			if (vecRight[i]->GetCollider() == nullptr)
			{
				continue;
			}

			//�ڱ� �ڽ��� �浹�Ϸ� �ϴ� ��쵵 ����
			if (vecLeft[i] == vecRight[i])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			//�� �浹ü�� ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = vecLeft[i]->GetCollider()->GetID();
			ID.Right_id = vecRight[j]->GetCollider()->GetID();
			
			iter = m_mapColInfo.find(ID.ID);

			//�� ������ �浹 ���� �ʿ� �������� ���� -> �浹���� �������� ����
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			//�� ������Ʈ�� �浹�� ���
			if (IsCollision(pLeftCol, pRightCol) == true)
			{
				//���� �浹 �� -> ���� �������� �浹 ���η� �б� �߻�
				if (iter->second == true)
				{
					//�������� �浹���̾���, ���ݵ� �浹 ��
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}

				else
				{
					//���� �浹 ����
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);

					iter->second = true;
				}
			}
			//�浹�� �ƴ� ���
			else
			{
				//���� �浹������ ������, ���������ӿ� �浹�ߴ� ���
				if (iter->second == true)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);

					iter->second = false;
				}
			}

		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vRightPos = _pRightCol->GetFinalPos();

	Vec2 vLeftScale = _pLeftCol->GetScale();
	Vec2 vRightScale = _pRightCol->GetScale();

	//�� ���� ������ �Ÿ���, �� ������Ʈ�� x, yũ�Ⱚ ���� ����(�浹���� �ʰ� �������� �� ����)���� ������ �浹 �߻�
	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f &&
		abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}
	return false;
}
