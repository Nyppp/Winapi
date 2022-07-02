#pragma once

class CObject;

class CCollider
{
private:
	//충돌체가 어떤 오브젝트의 충돌체인지 구분하기 위해,
	//멤버함수로 오브젝트 객체를 가진다.
	CObject* m_pOwner;
	
	//오프셋 -> fps 게임에서 헤드샷 구분같은 기능을 위해
	//충돌체 위치가 곧 오브젝트 위치가 아니라, 오프셋을 두어서
	//실제 위치와 충돌 위치의 차이를 둠
	Vec2 m_vOffsetPos;

	//위의 오프셋과, 오브젝트의 위치를 계산한 최종 충돌체의 위치
	Vec2 m_vFinalPos;

	//크기는 절대값으로 지정
	Vec2 m_vScale;

public:
	CCollider();
	~CCollider();

public:
	void finalupdate();

	friend class CObject;
};

