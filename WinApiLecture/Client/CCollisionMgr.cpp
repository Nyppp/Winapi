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
		//다음 그룹으로 넘어갈 수록, 이미 체크 한 관계가 있기 때문에 행을 iRow부터 시작
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			//충돌 관계 테이블을 둘러보면서 충돌관계가 성립되는 두 오브젝트가 있다면,
			//진짜로 두 물체가 충돌하는지 체크
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}

		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//작은 숫자를 가진 그룹타입을 행으로, 큰것을 열로 사용한다

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}


	//iRow번째 배열에, iCol만큼 1을 shift한 값을 집어넣는다(비트연산으로 2차원배열 대체)
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		//이미 존재한다면, 1의보수값과 and연산(해당 비트 부분만 반전)
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		//그 외에는 비트 삽입
		m_arrCheck[iRow] |= (1 << iCol);
	}

}

//그룹 간 충돌 갱신
void CCollisionMgr::CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	
	//반환타입으로 참조 타입을 반환하는 함수를 지역변수에 대입하면, 그것은 원본이 아님.
	//대입을 받는 변수도 const 참조 타입으로 지정해야 원본 자체를 가리키게 됨
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter;

	//두 그룹에 대한 모든 오브젝트들 탐색
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		//해당 오브젝트의 충돌체가 없다면 해당 오브젝트 생략
		if (vecLeft[i]->GetCollider() == nullptr)
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			//해당 오브젝트의 충돌체가 없다면 해당 오브젝트 생략
			if (vecRight[i]->GetCollider() == nullptr)
			{
				continue;
			}

			//자기 자신을 충돌하려 하는 경우도 생략
			if (vecLeft[i] == vecRight[i])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			//두 충돌체의 조합 아이디를 생성
			COLLIDER_ID ID;
			ID.Left_id = vecLeft[i]->GetCollider()->GetID();
			ID.Right_id = vecRight[j]->GetCollider()->GetID();
			
			iter = m_mapColInfo.find(ID.ID);

			//두 조합이 충돌 정보 맵에 존재하지 않음 -> 충돌하지 않음으로 저장
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			//두 오브젝트가 충돌한 경우
			if (IsCollision(pLeftCol, pRightCol) == true)
			{
				//현재 충돌 중 -> 이전 프레임의 충돌 여부로 분기 발생
				if (iter->second == true)
				{
					//이전에도 충돌중이었고, 지금도 충돌 중
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}

				else
				{
					//지금 충돌 시작
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);

					iter->second = true;
				}
			}
			//충돌이 아닌 경우
			else
			{
				//현재 충돌중이지 않지만, 이전프레임에 충돌했던 경우
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

	//두 중점 사이의 거리가, 두 오브젝트의 x, y크기값 합의 절반(충돌하지 않고 접해있을 때 길이)보다 작으면 충돌 발생
	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f &&
		abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}
	return false;
}
