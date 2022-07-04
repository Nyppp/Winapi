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

			//�� ������Ʈ�� �浹�� ���
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[i]->GetCollider()) == true)
			{
				//TODO : �̺�Ʈ Ȱ���� ������Ʈ �浹 �˻�
				//���� �������� �浹 ���θ� Ȱ���� �浹 ���� ����
				//���� �������� �浹 �ҷ����� ����� �ؽ� ���̺� �ڷᱸ���� �̿��� ������ �ҷ��ͼ� �浹 ������Ʈ
			}
			//�浹�� �ƴ� ���
			else
			{

			}

		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	return false;
}
