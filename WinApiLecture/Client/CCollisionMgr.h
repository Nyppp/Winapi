#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	//최대 32개(오브젝트 종류)만큼의 오브젝트간 충돌 관계를 담는 배열
	//비트 연산으로 구성되어 있으며, 만약 0번 오브젝트와 3번 오브젝트가 충돌 관계에 있고 나머지와는 충돌이 안되는 관계라면,
	//m_arrCheck[0] = 0000 0000 .... 0100 과 같이 저장됨(0x04)
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];

	//충돌체 간의 이전 프레임의 충돌 정보
	

public:
	void init();
	void update();

	//두 그룹의 충돌관계를 지정하는 함수
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	//충돌관계 초기화
	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
	}

private:
	//두 오브젝트 사이의 충돌 관계를 업데이트하는 함수
	void CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	//두 오브젝트가 충돌했는지 여부를 반환하는 함수
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);

};

