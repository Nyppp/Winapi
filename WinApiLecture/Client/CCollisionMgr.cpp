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

			//두 오브젝트가 충돌한 경우
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[i]->GetCollider()) == true)
			{
				//TODO : 이벤트 활용한 오브젝트 충돌 검사
				//이전 프레임의 충돌 여부를 활용해 충돌 동작 지정
				//이전 프레임의 충돌 불러오는 방법은 해쉬 테이블 자료구조를 이용해 빠르게 불러와서 충돌 업데이트
			}
			//충돌이 아닌 경우
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
